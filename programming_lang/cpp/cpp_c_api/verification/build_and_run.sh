

set -x

rm libcalculator_lib.dylib
cp ../build/libcalculator_lib.dylib ./
gcc -x c -o c_calculator c_calculator.c -L. -lcalculator_lib


DYLD_LIBRARY_PATH=$(pwd):${DYLD_LIBRARY_PATH} ./c_calculator
rm c_calculator libcalculator_lib.dylib
