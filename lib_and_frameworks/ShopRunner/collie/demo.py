# -*- coding: utf-8 -*-
# file: demo.py
# date: 2022-01-24


import duckdb
from pandas import DataFrame
from collie.cross_validation import stratified_split
from collie.interactions import Interactions
from collie.metrics import auc, evaluate_in_batches, mapk, mrr
from collie.model import MatrixFactorizationModel, CollieTrainer
from collie.movielens import read_movielens_df
from collie.utils import convert_to_implicit



if __name__ == "__main__":
    df: DataFrame = read_movielens_df()
    print(duckdb.query("select * from df limit 10").to_df())

    df_imp: DataFrame = convert_to_implicit(df)
    print(duckdb.query("select * from df_imp limit 10").to_df())

    interactions = Interactions(
        users=df_imp['user_id'], 
        items=df_imp['item_id'], 
        allow_missing_ids=True)
