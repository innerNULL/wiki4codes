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
    print(output)

    v = Visualizer(img[:, :, ::-1], MetadataCatalog.get(
        model_conf.get_config().DATASETS.TRAIN[0]), scale=1.2)
    #out = v.draw_instance_predictions(output["instances"].to("cpu"))
    i = 0
    tmp = []
    for box in output["instances"].pred_boxes.to('cpu'):
        score = output["instances"].scores[i]
        class_id = int(output["instances"].pred_classes[i]) + 1
        print(class_id)
        label = vdataset.coco.id2label(class_id)
        if score >= 0.92:
            #v.draw_instance_predictions(output["instances"][i])
            v.draw_box(box)
            v.draw_text(str(label), tuple(box[:2].numpy()))
        i += 1



    v = v.get_output()
    out_img = v.get_image()[:, :, ::-1]
    #out_img = out.get_image()[:, :, ::-1]
    cv2.namedWindow("image")
    cv2.imshow('image', out_img)
    cv2.waitKey(0)

    print(vdataset.coco.id2label)
    print(type(output))
    print(vpredictor.expt.detectron_out2objs)
    vpredictor.expt.detectron_out2objs(output)
