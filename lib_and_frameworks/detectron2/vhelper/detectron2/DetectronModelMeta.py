# -*- coding: utf-8 -*-
# file: DetectronModelMeta.py
# date: 2021-09-23


from multipledispatch import dispatch
from detectron2 import model_zoo

from .. import common



class DetectronModelMeta(common.ModelMeta):
    def __init__(self, 
            dataset: str, task: str, model: str, backbone: str
    ):
        self._dataset: str = None
        self._task: str = None
        self._model: str = None
        self._backbone: str = None
        self._name: str = None
        self._model_url: str = None
        self._conf_name: str = None

        self.init(dataset, task, model, backbone)

    def init(self, 
            dataset: str, task: str, model: str, backbone: str
    ) -> None:
        self._dataset = dataset
        self._task = task
        self._model = model
        self._backbone = backbone
        self._name = self._infer_model_name()
        self._model_url = self._infer_model_url()
        self._conf_name = self._infer_conf_name()

    def _infer_model_name(self) -> str:
        return "%s-%s-%s_%s" % (
                self._dataset, self._task, self._model, self._backbone)

    def _infer_model_url(self) -> str:
        sub_path: str = "%s-%s/%s_%s" % (
                self._dataset, self._task, self._model, self._backbone)
        model_url: str = model_zoo.get_checkpoint_url(sub_path + ".yaml")
        return model_url

    def _infer_conf_name(self) -> str:
        sub_path: str = "%s-%s/%s_%s" % (
                self._dataset, self._task, self._model, self._backbone)
        return sub_path + ".yaml"

    def get_name(self) -> str:
        return self._name

    def get_model_url(self) -> str:
        return self._model_url

    def get_conf_name(self) -> str:
        return self._conf_name


