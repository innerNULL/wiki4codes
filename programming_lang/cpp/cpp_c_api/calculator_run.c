// test_calculator.c
#include <stdio.h>
#include "./calculator_c_wrapper.h"

int main() {
    // Create a calculator instance
    CalculatorHandle calculator = createCalculator();

    // Use the calculator functions
    int result_add = add(calculator, 5, 3);
    int result_subtract = subtract(calculator, 8, 4);

    // Display the results
    printf("Result of addition: %d\n", result_add);
    printf("Result of subtraction: %d\n", result_subtract);

    // Destroy the calculator instance
    destroyCalculator(calculator);

    return 0;
}

