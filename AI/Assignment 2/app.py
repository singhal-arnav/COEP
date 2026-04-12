from fastapi import FastAPI
from pydantic import BaseModel
import joblib, numpy as np

app = FastAPI(title='WACR Prediction API', version='1.0')

model    = joblib.load('regression_model.pkl')
scaler   = joblib.load('scaler.pkl')
selector = joblib.load('selector.pkl')

class Features(BaseModel):
    Call_Amount:       float
    Call_Min:          float
    Call_Max:          float
    Triparty_Amount:   float
    Triparty_WACR:     float
    MarketRepo_Amount: float
    MarketRepo_WACR:   float
    Overnight_Total:   float
    MSF_Amount:        float
    MSF_Rate:          float
    SDF_Amount:        float
    SDF_Rate:          float
    DayOfWeek:         int
    Month:             int
    Year:              int

@app.get('/')
def root():
    return {'status': 'ok'}

@app.post('/predict')
def predict(f: Features):
    X_raw = np.array([[
        f.Call_Amount, f.Call_Min, f.Call_Max, f.Triparty_Amount,
        f.Triparty_WACR, f.MarketRepo_Amount, f.MarketRepo_WACR,
        f.Overnight_Total, f.MSF_Amount, f.MSF_Rate, f.SDF_Amount,
        f.SDF_Rate, f.DayOfWeek, f.Month, f.Year
    ]])
    X_sc  = scaler.transform(X_raw)
    X_sel = selector.transform(X_sc)
    pred  = model.predict(X_sel)[0]
    return {
        'predicted_WACR_pct': round(float(pred), 4),
        'interpretation': f'Predicted overnight call rate: {pred:.2f}% per annum'
    }
