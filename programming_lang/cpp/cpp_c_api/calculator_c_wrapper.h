// calculator_c_wrapper.h
#ifndef CALCULATOR_C_WRAPPER_H
#define CALCULATOR_C_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* CalculatorHandle;  // An opaque handle for the C++ class

CalculatorHandle createCalculator();
int add(CalculatorHandle handle, int a, int b);
int subtract(CalculatorHandle handle, int a, int b);
void destroyCalculator(CalculatorHandle handle);

#ifdef __cplusplus
}
#endif

#endif // CALCULATOR_C_WRAPPER_H

