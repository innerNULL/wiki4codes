# -*- coding: utf-8 -*-
# file: fetch_hist_data.py
# date: 2024-08-18


import pandas as pd
from openbb import obb
from pandas import DataFrame


def example_fetch_single_spot_hist_data(
    symbol: str="AAPL"
) -> DataFrame:
    return obb.equity.price.historical(symbol).to_df()


if __name__ == "__main__":
    print(example_fetch_single_spot_hist_data())
