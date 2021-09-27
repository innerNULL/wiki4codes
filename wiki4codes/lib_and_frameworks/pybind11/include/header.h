

#include <stdint.h> 
#include <string>
#include <vector>
#include <spdlog/spdlog.h>
#include <absl/strings/str_split.h> 
#include <pybind11/pybind11.h>

namespace py = pybind11;      


namespace pbd11_test {


int32_t add_int(int a, int b);


void print_str(const std::string& str);


void print_str_ptr(const std::string* str_ptr);


class Person {
 public:
  Person(int32_t age);
  int32_t get_age();
  int32_t give_age(int32_t give_age);
  int32_t give_age(std::string give_age);

 private:
  int32_t age;
};


void random_log();


std::vector<std::string> str_split(
    const std::string& str, const std::string& delimiter);


void pybind(py::module &m);


} // namespace pbd11_test
