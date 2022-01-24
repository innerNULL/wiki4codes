# -*- coding: utf-8 -*-
# file: example.py
# date: 2021-08-01


import detectron2
from detectron2.utils.logger import setup_logger
setup_logger()

import os
import numpy as np
import cv2
import random
import numpy as np
#from google.colab.patches import cv2_imshow

from detectron2 import model_zoo
from detectron2.engine import DefaultPredictor
from detectron2.config import get_cfg
from detectron2.utils.visualizer import Visualizer
from detectron2.data import MetadataCatalog
from detectron2.modeling import build_model

from utils import test


def get_model(
        dataset: str="COCO", task: str="Detection", 
        model: str="faster_rcnn", 
        backbone: str = "R_101_FPN_3x", 
        if_pretrained: bool = True, 
        cache_path: str="./", 
        weight_file_subpath: str="weights"
) -> DefaultPredictor:
    cfg = get_cfg()
    cfg.MODEL.DEVICE = "cpu"

    weights_dir: str = "%s/%s" % (cache_path, weight_file_subpath)
    if not os.path.exists(cache_path):
        os.system("mkdir -p %s" % weights_dir)

    model_name: str = "%s-%s/%s_%s" % (dataset, task, model, backbone)
    adj_model_name: str = model_name.replace("/", "-")
    target_cfg_file = model_zoo.get_config_file(model_name + ".yaml")
    cfg.merge_from_file(target_cfg_file)

    #model = build_model(cfg)
    
    target_weights_url = model_zoo.get_checkpoint_url(model_name + ".yaml")
    model_path = "%s/%s.pkl" % (weights_dir, adj_model_name)
    model_path = test.get_url_file(
            target_weights_url, model_path, False)
    #cfg.MODEL.WEIGHTS = model_zoo.get_checkpoint_url(target_weights_url)
    cfg.MODEL.WEIGHTS = model_path
    model = DefaultPredictor(cfg)
    
    model_pkg = {"model": model, "cfg": cfg}
    return model_pkg




def main() -> int:
    img_path: str = test.get_url_file(
        "http://seopic.699pic.com/photo/50114/7683.jpg_wh1200.jpg", 
        "dev.jpg", False)
    img = cv2.imread("./dev.jpg")  
    model_pkg = get_model(cache_path="~/Cache/detectron2")
    model = model_pkg["model"]

    output = model(img)
    #print(output)
    print(output["instances"].pred_classes)
    print(output["instances"].pred_boxes)

    v = Visualizer(img[:, :, ::-1], MetadataCatalog.get(model_pkg["cfg"].DATASETS.TRAIN[0]), scale=1.2)
    out = v.draw_instance_predictions(output["instances"].to("cpu"))

    out_img = out.get_image()[:, :, ::-1]
    print(type(out_img))
    cv2.namedWindow("image")
    cv2.imshow('image', out_img)
    cv2.waitKey(0)
    return 0


if __name__ == "__main__":
    main()
