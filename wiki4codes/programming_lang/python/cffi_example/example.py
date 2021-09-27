# -*- coding: utf-8 -*-


import os
from cffi import FFI
from typing import Dict, List, Union


def c_src_parsing(c_src_path: str) -> Dict:
    output = {"include": "", "core": ""}
    c_src_file = open(c_src_path, 'r')

    line = c_src_file.readline()
    while line:
        if "#include" in line:
            output["include"] = output["include"] + line
        else:
            output["core"] = output["core"] + line
        line = c_src_file.readline()
    
    #output["include"] = output["include"] + '#include "{0}"\n'.format(c_src_path)
    return output


def test():
    print("1 + 2 = {}".format(c_demo.add_test(1, 2)))

    # Wrong: x = ffi.new("char[]", "hello")
    x = ffi.new("char[]", "hello".encode('ascii'))
    c_demo.print_test(x)

    int_array = ffi.new("int[]", [1,2,3])
    c_demo.print_int_array(int_array, 3)


def test_feature_struct():
    user = {
        "user_id": 123, "user_type": 2, 
        "gender": ffi.new("char[]", "male".encode('ascii')), 
        "city": ffi.new("char[]", "beijing".encode('ascii'))
    }
    doc = {"doc_id": 456, "doc_type": 1}
    fea = {"user": user, "doc": doc}
    print(fea)
    feature = ffi.new("Feature*", fea)
    c_demo.print_feature_obj(feature) 

    feature_obj_array = ffi.new("Feature[]", [fea, fea, fea, fea])
    c_demo.print_feature_obj_array(feature_obj_array, 4)


def test_demo_obj_struct():
    v = ffi.new("DemoObj*", 
        {
            'a': 1, 'b': 999, 'c': 3.2, 'd': 3.14, 
            'e': ffi.new("char[]", "hello".encode('ascii'))
        }
    )
    c_demo.print_demo_obj(v)
    print("v.a: ", v.a)


C_SRC_ROOT = "./c_src"
TYPES_HEADER_FILE = "./c_src/types.h"
FUNCS_HEADER_FILE = "./c_src/funcs.h"
FUNCS_SRC_FILE = "./c_src/funcs.c"




if __name__ == "__main__":
    print("python-cffi lib example")

    ffibuilder = FFI()
    ffi = FFI()

    parsed_types_header = c_src_parsing(TYPES_HEADER_FILE)
    ffibuilder.cdef(parsed_types_header["core"])

    parsed_funcs_header = c_src_parsing(FUNCS_HEADER_FILE)
    ffibuilder.cdef(parsed_funcs_header["core"])

    ffibuilder.set_source(
        '_demo', 
        parsed_types_header["include"] + parsed_funcs_header["include"], 
        sources=[FUNCS_SRC_FILE], 
        library_dirs=['.'],
        include_dirs=[C_SRC_ROOT], 
        extra_compile_args=['-O3', '-march=native', '-ffast-math']
    )
    ffibuilder.compile(verbose=True)

    
    import _demo.lib as c_demo
    from _demo import ffi

    test()
    test_demo_obj_struct()
    test_feature_struct()
