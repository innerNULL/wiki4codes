# -*- coding: utf-8 -*-
# file: utils.py
# date: 2021-09-23


from typing import Dict


def get_model_meta(
        dataset: str,
        task: str, 
        model: str, 
        backbone: str
) -> Dict[str, str]:
    model_meta: Dict[str, str] = {}
    model_meta["dataset"] = dataset
    model_meta["task"] = task
    #model_meta["model"]
    return model_meta
