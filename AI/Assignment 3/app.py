from fastapi import FastAPI
from pydantic import BaseModel
import joblib
import numpy as np
import pandas as pd

app = FastAPI(title='Indore Rural-Urban Health Classifier')

model = joblib.load('classifier_model.pkl')
scaler = joblib.load('scaler.pkl')
selector = joblib.load('selector.pkl')
num_imp = joblib.load('num_imputer.pkl')
le = joblib.load('label_encoder.pkl')

class Features(BaseModel):
    Age: float
    Age_Code: str
    Sex: str
    Weight_in_kg: float
    Length_height_cm: float
    BP_systolic: float
    BP_Diastolic: float
    Pulse_rate: float
    fasting_blood_glucose_mg_dl: float
    Haemoglobin_test: str
    test_salt_iodine: float
    ahs_house_unit: float
    house_hold_no: float

@app.post('/predict')
def predict(f: Features):
    age_years = f.Age / 12 if f.Age_Code.strip().lower() == 'months' else f.Age
    
    raw_numerical = np.array([[
        age_years, 
        f.Weight_in_kg, 
        f.Length_height_cm, 
        f.BP_systolic, 
        f.BP_Diastolic, 
        f.Pulse_rate, 
        f.fasting_blood_glucose_mg_dl, 
        f.test_salt_iodine,
        f.ahs_house_unit,
        f.house_hold_no
    ]])
    
    imputed_data = num_imp.transform(raw_numerical)
    
    sex_val = 1 if f.Sex.strip().lower() == 'male' else 0
    hemo_val = 1 if f.Haemoglobin_test.strip().lower() == 'yes' else 0
    
    final_features = np.column_stack((imputed_data, [[sex_val, hemo_val]]))
    
    X_sc = scaler.transform(final_features)
    X_sel = selector.transform(X_sc)
    
    pred_idx = model.predict(X_sel)[0]
    label = le.inverse_transform([pred_idx])[0]
    
    proba = None
    if hasattr(model, 'predict_proba'):
        proba = model.predict_proba(X_sel)[0]
    
    return {
        'predicted_class': str(label),
        'class_probabilities': dict(zip(le.classes_, proba.tolist())) if proba is not None else "N/A"
    }
