# -*- coding: utf-8 -*-
# file: example.py
# date: 2021-09-23


import sys
import cv2
from typing import Dict
from detectron2.data import MetadataCatalog
from detectron2.utils.visualizer import Visualizer

import vhelper
import vhelper.detectron2 as vdetectron2
import vhelper.dataset as vdataset
import vhelper.predictor as vpredictor


IMG_PATH: str = sys.argv[1]


if __name__ == "__main__":
    model_meta: Dict = vdetectron2.get_model_meta(
            "COCO", "Detection", "faster_rcnn", "R_101_FPN_3x")
    print(model_meta)
    
    model_meta = vdetectron2.DetectronModelMeta(
            "COCO", "Detection", "faster_rcnn", "R_101_FPN_3x")
    model_conf = vdetectron2.DetectronModelConfig("_tmp", "cpu")
    model_conf.config(model_meta)

    model = model_conf.get_model()

    img = cv2.imread(IMG_PATH) 
    output = model(img)
    tags = vpredictor.expt.detectron_out2objs(output)
    print(tags)
