#ifndef MEASUREMENT_HELPER_H
#define MEASUREMENT_HELPER_H

#include <Arduino.h>

// Declaration of the helper function that measures execution time and free heap memory.
// The function takes a label (for printing) and a pointer to a function (with no arguments and no return).
void measureAndPrint(const char* label, void (*commandFunc)());

#endif // MEASUREMENT_HELPER_H
