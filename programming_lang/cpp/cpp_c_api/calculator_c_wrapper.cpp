// calculator_c_wrapper.cpp
#include "calculator_c_wrapper.h"
#include "calculator.hpp"

extern "C" {

CalculatorHandle createCalculator() {
    return new Calculator();
}

int add(CalculatorHandle handle, int a, int b) {
    return static_cast<Calculator*>(handle)->add(a, b);
}

int subtract(CalculatorHandle handle, int a, int b) {
    return static_cast<Calculator*>(handle)->subtract(a, b);
}

void destroyCalculator(CalculatorHandle handle) {
    delete static_cast<Calculator*>(handle);
}

} // extern "C"

