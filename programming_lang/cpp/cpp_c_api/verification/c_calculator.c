// example_c_usage.c
//
// gcc ./c_calculator.c -o c_calculator -l ../build/libcalculator_lib.dylib

#include <stdio.h>
#include "../calculator_c_wrapper.h"

int main() {
    CalculatorHandle calculator = createCalculator();
    int result_add = add(calculator, 5, 3);
    int result_subtract = subtract(calculator, 8, 4);
    printf("adding result: %i\n", result_add);
    printf("subtraction result: %i\n", result_subtract);
    // Use results as needed
    destroyCalculator(calculator);
    return 0;
}

