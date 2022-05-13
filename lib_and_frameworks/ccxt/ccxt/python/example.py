# -*- coding: utf-8 -*-
# file: example.py
# date: 2022-05-21


import ccxt
from ccxt.binance import binance


def show_exchhanges() -> None:
    print(ccxt.exchanges)


def git_exchange_binance() -> None:
    return ccxt.binance()


if __name__ == "__main__":
    show_exchhanges()
    ex = git_exchange_binance()
    #kline = ex.fetchOHLCV('ETH/USDT', timeframe='1d', limit=100)
    kline = ex.fetchOHLCV('ETH/USDT', timeframe='1m', limit=100) 
    print(kline)
