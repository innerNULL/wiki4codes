# -*- coding: utf-8 -*-
# file: base_examples.py
# date: 2022-06-20


import random
import talipp
from typing import List
from talipp.indicators import MACD


OPEN: List[float] = random.sample(range(1, 10000), 1000) 
CLOSE: List[float] = random.sample(range(1, 10000), 1000)
HIGH: List[float] = random.sample(range(1, 10000), 1000)
LOW: List[float] = random.sample(range(1, 10000), 1000)


if __name__ == "__main__":
    macd = MACD(12, 26, 9, CLOSE)[-1]
    print(macd)
