# -*- coding: utf-8 -*-
# file: fast_kmeans.pt
# date: 2022-07-09


import argparse
import numpy as np
from typing import Dict, List
from argparse import Namespace
from argparse import ArgumentParser
from numpy import ndarray
from sklearn.cluster import KMeans


parser: ArgumentParser = argparse.ArgumentParser(
    description='Arguments')
parser.add_argument(
    "--data", default="./data.txt", type=str, 
    help="Training data path.")
parser.add_argument(
    "--kv_sep", default=" ", 
    help="ID and vector seperator.")
parser.add_argument(
    "--vec_sep", default=" ", 
    help="Vector's elements seperator.")
parser.add_argument(
    "--cluster_num", default=16, type=int,  
    help="Number of clusters")

args: Namespace = parser.parse_args()


def load_data(
    path: str, kv_sep: str, vec_sep: str
) -> ndarray:
    ids: List[int] = []
    data: List[List[float] ] = []
    data_file = open(path, 'r')
    line = data_file.readline()
    while line:
        line = line.strip("\n")
        record_id: int = int(line.split(kv_sep)[0])
        vec: List[float] = [
            float(x) for x 
            in kv_sep.join(line.split(kv_sep)[1:]).split(vec_sep)
        ]
        ids.append(record_id)
        data.append(vec)
        line = data_file.readline()

    data_file.close()
    return (ids, np.array(data))



if __name__ == "__main__":
    ids, inputs = load_data(args.data, args.kv_sep, args.vec_sep)
    kmeans: KMeans = KMeans(n_clusters=args.cluster_num, random_state=0).fit(inputs)
    labels: List[int] = list(kmeans.labels_)
    cluster_stat: Dict[int, int] = {}
    for label in labels:
        if label not in cluster_stat:
            cluster_stat[label] = 0
        cluster_stat[label] += 1
    print(cluster_stat)
    print(kmeans.cluster_centers_)
