from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from typing import List
import joblib, numpy as np

app = FastAPI(title="PLFS Household Clustering API", version="1.0")
bundle = joblib.load("saved_model/clustering_model.pkl")

class PredictRequest(BaseModel):
    features: List[List[float]]

class PredictResponse(BaseModel):
    cluster_labels: List[int]
    model_name: str
    n_clusters: int

@app.get("/health")
def health():
    return {
        "status": "ok",
        "model": bundle["model_name"],
        "n_clusters": bundle["n_clusters"],
        "features": bundle["feature_cols"],
        "trained_on": bundle["trained_on"]
    }

@app.post("/predict", response_model=PredictResponse)
def predict(req: PredictRequest):
    try:
        X = np.array(req.features)
        if X.shape[1] != len(bundle["feature_cols"]):
            raise HTTPException(
                status_code=400,
                detail=f"Expected {len(bundle['feature_cols'])} features, got {X.shape[1]}"
            )
        X_sc = bundle["scaler"].transform(X)
        labels = bundle["model"].predict(X_sc).tolist()
        return PredictResponse(
            cluster_labels=labels,
            model_name=bundle["model_name"],
            n_clusters=bundle["n_clusters"]
        )
    except HTTPException:
        raise
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
