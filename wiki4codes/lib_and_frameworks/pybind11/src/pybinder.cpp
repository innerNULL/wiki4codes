

#include <iostream>
#include <pybind11/pybind11.h>

#include "./header.h"
#include "./header1.h"


namespace py = pybind11;


namespace pbd11_test {  


PYBIND11_MODULE(pymod, m) {
  pybind(m);
  pybind1(m);
}


}
