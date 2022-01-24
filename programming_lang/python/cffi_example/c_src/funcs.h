

//#ifndef SRC_DEMO_H_
//#define SRC_DEMO_H_


#include <stdio.h>
#include <pthread.h>
#include "./types.h"

int add_test(int a, int b);


void print_test(const char* input);


void print_demo_obj(DemoObj* input);


void print_feature_obj(Feature* input);


void print_int_array(int* array, int size);


void print_feature_obj_array(Feature* inputs, int size);


//#endif
