# -*- coding: utf-8 -*-
# file: expt.py


from .. import dataset


def detectron_out2objs(outputs, min_score=0.9):
    output = []
    pred_classes = outputs["instances"].pred_classes
    scores = outputs["instances"].scores
    assert len(pred_classes) == len(scores)
    for i in range(len(scores)):
        score = float(scores[i])
        pred_class = int(pred_classes[i])
        pred_class_name = dataset.coco.id2label(pred_class + 1)
        pred_class_cn_name = dataset.coco.en_label2cn_label(pred_class_name)
        if score >= min_score:
            output.append([pred_class_cn_name, score])
    return output

