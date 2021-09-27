

#include <stdint.h> 
#include <string>
#include <pybind11/pybind11.h>

namespace py = pybind11;      


namespace pbd11_test {


int32_t add_int1(int a, int b);


void print_str1(const std::string& str);


void print_str_ptr1(const std::string* str_ptr);


class Person1 {
 public:
  Person1(int32_t age);
  int32_t get_age();

 private:
  int32_t age;
};


void pybind1(py::module &m);


} // namespace pbd11_test
