

#include <iostream>
//#include <pybind11/pybind11.h>

#include "./header1.h"

namespace py = pybind11;


namespace pbd11_test {  


int32_t add_int1(int32_t a, int32_t b) {
  return a + b;
}


void print_str1(const std::string& str) {
  std::cout << str << std::endl;  
}


void print_str_ptr1(const std::string* str_ptr) {
  std::cout << "string instance at " << str_ptr 
      << " is " << *str_ptr << std::endl;
}


Person1::Person1(int32_t age) {
  this->age = age;
}


int32_t Person1::get_age() {
  return this->age;
}


//PYBIND11_MODULE(pymod, m) {
void pybind1(py::module &m) { 
  m.def("add_int1", &add_int1, "A function which adds two numbers");

  m.def("print_str1", &print_str1, "A function print string");

  m.def("print_str_ptr1", &print_str_ptr1, "A function print a pointer points a string");

  py::class_<Person1>(m, "Person1")
      .def(py::init<int32_t>())
      .def("get_age", &Person1::get_age);

}


}
