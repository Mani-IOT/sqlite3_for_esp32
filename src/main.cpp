#include <Arduino.h>
#include "sqlite3ForEsp32.h"
#include "Measure_Lib.h"

// Database file path.
#define DATABASE_PATH "/spiffs/test.db"

SQLite3ForEsp32* database = nullptr;

void setup() {
  Serial.begin(115200);
  // Optionally wait for the Serial Monitor to open (useful with native USB boards).
  while (!Serial) { }
  delay(2000);  // Allow time for system startup.

  // Instantiate the SQLite3ForEsp32 class.
   // Measure the object creation: allocate the SQLite3ForEsp32 object.
  measureAndPrint("Object Creation", [](){
    // Create the object and assign it to the global pointer.
    database = new SQLite3ForEsp32(DATABASE_PATH);
  });

  // Initialize SPIFFS and measure execution.
  measureAndPrint("initializeSPIFFS", [](){
    database->initializeSPIFFS();
  });
  
  // Create table.
  measureAndPrint("createTable", [](){
    database->createTable();
  });
  
  // Add data.
  measureAndPrint("addData (\"Hello, World!\")", [](){
    database->addData("Hello, World!");
  });
  
  measureAndPrint("addData (\"ESP32 is awesome!\")", [](){
    database->addData("ESP32 is awesome!");
  });
  
  // Print data.
  measureAndPrint("printData", [](){
    database->printData();
  });
  
  // Update a row.
  measureAndPrint("updateRow (id = 1)", [](){
    database->updateRow(1, "Updated Value");
  });
  
  // Delete a row.
  measureAndPrint("deleteRow (id = 2)", [](){
    database->deleteRow(2);
  });
  
  // Print data again.
  measureAndPrint("printData (after modifications)", [](){
    database->printData();
  });
}

void loop() {
  // Empty loop.
}
