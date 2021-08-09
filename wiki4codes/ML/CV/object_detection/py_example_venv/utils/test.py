# -*- coding: utf-8 -*-
# file: test.py
# date: 2021-08-02


import os


def get_url_file(url: str, path: str=None, 
        if_overwrite: bool=False) -> str:
    if path is None:
        path = os.path.split(url)[-1]
    
    path = os.path.expanduser(path)
  
    if os.path.exists(path):
        if not if_overwrite:
            print("%s has been already exists..." % path)
            return path
        os.system("mv %s %s.bak" % (path, path))

    os.system("wget %s -O %s" % (url, path))
    return path
