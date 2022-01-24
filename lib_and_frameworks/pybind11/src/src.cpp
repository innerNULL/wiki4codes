

#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

#include "./header.h"

namespace py = pybind11;


namespace pbd11_test {  


int32_t add_int(int32_t a, int32_t b) {
  return a + b;
}


void print_str(const std::string& str) {
  std::cout << str << std::endl;  
}


void print_str_ptr(const std::string* str_ptr) {
  std::cout << "string instance at " << str_ptr 
      << " is " << *str_ptr << std::endl;
}


Person::Person(int32_t age) {
  this->age = age;
}


int32_t Person::get_age() {
  return this->age;
}


int32_t Person::give_age(int32_t give_age) {
  this->age = give_age;
  return give_age;
}


int32_t Person::give_age(std::string give_age) {
  return this->give_age(std::stoi(give_age));
}


void random_log() {
  spdlog::info("I'm random log");
}


std::vector<std::string> str_split(
    const std::string& str, const std::string& delimiter) {
  std::vector<std::string> output = absl::StrSplit(str, delimiter); 
  return output;
}


//PYBIND11_MODULE(pymod, m) {
void pybind(py::module &m) {
  m.def("add_int", &add_int, "A function which adds two numbers");

  m.def("print_str", &print_str, "A function print string");

  m.def("print_str_ptr", &print_str_ptr, "A function print a pointer points a string");

  m.def("random_log", &random_log, "A demo of using header-only cpp lib such as spdlog.");

  m.def("str_split", &str_split, 
          "1. A demo of linking cpp third-party lib to pybind python module, 2. A demo of let function return some complex cpp data-structure such as a iterator.");

  py::class_<Person>(m, "Person")
      .def(py::init<int32_t>())
      .def("get_age", &Person::get_age)
      //.def("give_age", &Person::give_age) /// Error since this is an overloaded member function.
      //.def("give_age", py::overload_cast<int32_t>(&Person::give_age)) /// Also not work since pybind didn't do well on `py::overload_cast`
      .def("give_age", static_cast<int32_t (Person::*)(int32_t)>(&Person::give_age))
      .def("give_age", static_cast<int32_t (Person::*)(std::string)>(&Person::give_age));
}


}
