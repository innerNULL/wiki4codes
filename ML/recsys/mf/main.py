# -*- coding: utf-8 -*- 
# file: run_data_gen.py
# date: 2022-07-08


import os
import shutil
import random
from typing import Dict, List, Tuple


class DataMeta:
    user2id: Dict[str, int] = {}
    id2user: Dict[int, str] = {}
    item2id: Dict[str, int] = {}
    id2item: Dict[int, str] = {}
    readlist: Dict[int, List[int]] = {}
    item_dist: Dict[int, float] = {}
    size: int = 0
    path: str = "./_out"


def get_meta(
    data_meta: DataMeta, 
    csv: str, 
    user_name_col: int, user_id_col: int, 
    item_name_col: int, item_id_col: int, 
    head: bool=True, delimiter: str=","
) -> None:
    csv_file = open(csv, 'r')
    line: str = csv_file.readline()
    if head:
        line = csv_file.readline()
    while line:
        fields: List[str] = line.strip("\n").split(delimiter)

        try:
            assert(len(fields) == 4)
            user_name: str = fields[user_name_col]
            user_id: int = int(fields[user_id_col])
            item_name: str = fields[item_name_col]
            item_id: int = int(fields[item_id_col])
           
            if user_id not in data_meta.readlist:
                data_meta.readlist[user_id] = []
            if item_id not in data_meta.item_dist:
                data_meta.item_dist[item_id] = 0.0
            
            data_meta.user2id[user_name] = user_id
            data_meta.item2id[item_name] = item_id
            data_meta.id2user[user_id] = user_name
            data_meta.id2item[item_id] = item_name
            data_meta.readlist[user_id].append(item_id)
            data_meta.item_dist[item_id] += 1.0
            data_meta.size += 1

        except Exception as e:
            print(e)
            print(fields)

        line = csv_file.readline()

    csv_file.close()
    #assert(len(name2id) == len(id2name))
    data_meta.item_dist = dict([
        (k, v / data_meta.size) 
        for k, v in data_meta.item_dist.items()
    ])


def out_meta(data_meta: DataMeta) -> None:
    user2id_file = open(os.path.join(data_meta.path, "user2id.txt"), "w")
    id2user_file = open(os.path.join(data_meta.path, "id2user.txt"), "w")
    item2id_file = open(os.path.join(data_meta.path, "item2id.txt"), "w")
    id2item_file = open(os.path.join(data_meta.path, "id2item.txt"), "w")

    for k, v in data_meta.user2id.items():
        user2id_file.write("{},{}\n".format(k, v))
    for k, v in data_meta.id2user.items():
        id2user_file.write("{},{}\n".format(k, v))
    for k, v in data_meta.id2item.items():
        id2item_file.write("{},{}\n".format(k, v))

    user2id_file.close()
    id2user_file.close()
    item2id_file.close()
    id2item_file.close()


def build_data(
    data: DataMeta, 
    test_ratio: float=0.15, sampling_ratio: int = 1
) -> Tuple[str, str]:
    path = data.path
    try:
        shutil.rmtree(path)
    except Exception as e:
        print(e)
    os.mkdir(path)
    training = open(os.path.join(path, "training.txt"), 'w')
    test = open(os.path.join(path, "test.txt"), 'w')

    # NOTE
    # This is to make sure each user/item id should exists in 
    # both training and test data, or qmf will raise error.
    user_recorder: Dict[int, bool] = {}
    item_recorder: Dict[int, bool] = {}

    for user_id, readlist in data.readlist.items():
        for item_id in readlist:
            record: str = "{} {} 2".format(user_id, item_id)
            if random.uniform(0, 1) < test_ratio \
                    and user_id in user_recorder \
                    and item_id in item_recorder:
                test.write(record + "\n")
            else:
                training.write(record + "\n")
                user_recorder[user_id] = True
                item_recorder[item_id] = True
            for i in range(sampling_ratio):
                while True:
                    # Sampling by uniform
                    #neg_item_id: int = random.sample(
                    #    data.id2item.items(), 1)[0][0]
                    pool: List[int] = [k for k, v in data.item_dist.items()]
                    dist: List[float] = [v for k, v in data.item_dist.items()]
                    neg_item_id: int = random.choices(pool, dist)[0]
                    if neg_item_id != item_id:
                        record: str = "{} {} 1".format(user_id, neg_item_id)
                        #print(record)
                        if random.uniform(0, 1) < test_ratio:
                            test.write(record + "\n")
                        else:
                            training.write(record + "\n")
                        break

    training.close()
    test.close()

    out_meta(data)
    return


if __name__ == "__main__":
    # Suppost the data format is:
    # user_name, item_name, user_id, item_id
    data_meta = DataMeta()
    get_meta(data_meta, "./joint_data.csv", 0, 2, 1, 3)
    #print(data_meta.item_dist)
    build_data(data_meta, sampling_ratio=1)
    #build_data(data_meta, sampling_ratio=2)
