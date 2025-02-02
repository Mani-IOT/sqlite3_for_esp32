#include "Measure_Lib.h"

void measureAndPrint(const char* label, void (*commandFunc)()) {
  // Get free memory before executing the command.
  int freeBefore = ESP.getFreeHeap();
  // Get the start time (in microseconds).
  unsigned long startTime = millis();
  
  // Execute the command.
  commandFunc();
  
  // Calculate elapsed time.
  unsigned long elapsedTime = millis() - startTime;
  // Get free memory after executing the command.
  int freeAfter = ESP.getFreeHeap();
  
  // Print the label, execution time, and memory details.
  Serial.printf("\n MeasureAPI - %s : Duration: %lu ms, Free Heap Before: %d bytes, Free Heap After : %d bytes, Heap Delta : %d bytes\n\n",
                label, elapsedTime, freeBefore, freeAfter, freeBefore - freeAfter);
}
