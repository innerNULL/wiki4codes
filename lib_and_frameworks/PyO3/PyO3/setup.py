# -*- coding: utf-8 -*-
# file: setup.py
# date: 2022-03-21


import os
import sys
from setuptools import setup


if __name__ == "__main__":
    os.system("{} -m pip install setuptools_rust".format(
        sys.executable))
    from setuptools_rust import RustExtension
    
    setup(
        name="extension_rust", 
        rust_extensions=[
            RustExtension(
                "extension_rust",
                debug=os.environ.get("BUILD_DEBUG") == "1", 
                path="./extensions/rust/Cargo.toml"
            )
        ]
    )
