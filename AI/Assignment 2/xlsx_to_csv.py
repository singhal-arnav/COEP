import pandas as pd
import numpy as np
import sys
import os

def convert(xlsx_path: str, csv_path: str) -> None:
    df_raw = pd.read_excel(xlsx_path, header=None)

    data = df_raw.iloc[6:, 1:].copy()
    data.columns = range(data.shape[1])

    col_map = {
        0:  'Date',
        1:  'Call_Amount',
        2:  'Call_WACR',
        3:  'Call_Min',
        4:  'Call_Max',
        5:  'Triparty_Amount',
        6:  'Triparty_WACR',
        9:  'MarketRepo_Amount',
        10: 'MarketRepo_WACR',
        17: 'Overnight_Total',
        42: 'MSF_Amount',
        43: 'MSF_Rate',
        44: 'SDF_Amount',
        45: 'SDF_Rate',
    }

    data = data.rename(columns=col_map)[list(col_map.values())]
    data = data.replace('-', np.nan)
    data['Date'] = pd.to_datetime(data['Date'], errors='coerce')

    for col in list(col_map.values())[1:]:
        data[col] = pd.to_numeric(data[col], errors='coerce')

    data = (
        data
        .dropna(subset=['Date'])
        .sort_values('Date')
        .reset_index(drop=True)
    )

    data['Date'] = data['Date'].dt.strftime('%Y-%m-%d')
    data.to_csv(csv_path, index=False)
    print(f"Saved {len(data)} rows x {len(data.columns)} columns → {csv_path}")


if __name__ == '__main__':
    xlsx = sys.argv[1] if len(sys.argv) > 1 else 'Daily Money Market Operations.xlsx'
    csv  = sys.argv[2] if len(sys.argv) > 2 else os.path.splitext(xlsx)[0] + '.csv'
    convert(xlsx, csv)
