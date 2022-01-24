/// file: example.cpp
/// date: 2022-01-07


#include <iostream>
#include <string>
#include <vector>
#include <absl/strings/str_join.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
//#include <pybind11/pybind11.h>


int main(int argc, char** argv) {
  spdlog::info("Welcome to ExternalProject_example!"); 

  std::vector<std::string> v = {"foo","bar","baz"};
  std::string s = absl::StrJoin(v, "-");

  nlohmann::json obj;
  obj["field0"] = "a";

  std::cout << "Joined string is: " << s << "\n";
  spdlog::info("Finished.");
  return 0;
}
