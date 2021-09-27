# -*- coding: utf-8 -*-
# file: DetectronModelConfig.py
# date: 2021-09-23


import os
from detectron2.config import get_cfg
from detectron2 import model_zoo
from detectron2.engine import DefaultPredictor

from .. import common
from .DetectronModelMeta import *


class DetectronModelConfig(common.ModelConfig):
    def __init__(self, 
            root_path: str, device: str):
        self._root_path = None
        self._device = None
        self._conf_core = None
        self._model_meta = None
        self._model_path = None

        self.init(root_path, device)

    def init(self, 
            root_path: str, device: str) -> None:
        self._root_path = os.path.abspath(root_path)
        self._device = device
        self._conf_core = get_cfg()

    def config(self, model_meta: DetectronModelMeta) -> None:
        self._model_meta = model_meta
        self._path_task()
        self._download_task()
        self._config_task()

    def _path_task(self) -> None:
        os.system("mkdir -p %s" % self._root_path)

    def _download_task(self) -> None:
        model_path: str = "%s/%s.pkl" % (
                self._root_path, self._model_meta.get_name())
        self._model_path = model_path
        if not os.path.exists(model_path):
            os.system("wget %s -O %s" % (
                self._model_meta.get_model_url(), model_path))

    def _config_task(self) -> None:
        self._conf_core.MODEL.DEVICE = self._device
        target_cfg_file = model_zoo.get_config_file(
                self._model_meta.get_conf_name())
        self._conf_core.merge_from_file(target_cfg_file)
        self._conf_core.MODEL.WEIGHTS = self._model_path
        
    def get_config(self):
        return self._conf_core

    def get_model(self):
        return DefaultPredictor(self._conf_core)


