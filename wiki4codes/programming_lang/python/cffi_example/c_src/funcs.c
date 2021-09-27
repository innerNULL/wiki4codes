

#include "./funcs.h"


int add_test(int a, int b) {
  return a + b;
}


void print_test(const char* input) {
  printf("print_test:\n");
  printf("\t%s\n", input);
}


void print_demo_obj(DemoObj* input) {
  printf("print_demo_obj:\n");
  printf("\ta: %i\n", input->a);
  printf("\tb: %li\n", input->b);
  printf("\tc: %f\n", input->c);
  printf("\td: %f\n", input->d);
  printf("\te: %s\n", input->e);
}


void print_feature_obj(Feature* input) {
  printf("print_feature_obj:\n");
  printf("  user:\n");
  printf("    user_id: %li\n", input->user.user_id);
  printf("    user_type: %i\n", input->user.user_type);
  printf("    gender: %s\n", input->user.gender);
  printf("    city: %s\n", input->user.city);
  printf("  doc:\n");
  printf("    doc_id: %li\n", input->doc.doc_id);
  printf("    doc_type: %i\n", input->doc.doc_type);
}


void print_int_array(int* array, int size) {
  for (int i = 0; i < size; ++i) {
    printf("%i-th element: %i\n", i, *(array + i));
  }
}


void print_feature_obj_array(Feature* inputs, int size) {
  for (int i = 0; i < size; ++i) {
    printf("%i-th element: \n", i);
    print_feature_obj(inputs + i);
  }
}
