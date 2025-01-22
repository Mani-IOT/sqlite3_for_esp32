#include "sqlite3ForEsp32.h"

// Database file path
#define DATABASE_PATH "/spiffs/test.db"

// Instantiate the SQLite3ForEsp32 class
SQLite3ForEsp32 database(DATABASE_PATH);

void setup() {
    Serial.begin(115200);

    // Initialize SPIFFS
    database.initializeSPIFFS();

    // Create table
    database.createTable();

    // Add data
    database.addData("Hello, World!");
    database.addData("ESP32 is awesome!");

    // Print data
    database.printData();

    // Update a row
    database.updateRow(1, "Updated Value");

    // Delete a row
    database.deleteRow(2);

    // Print data again
    database.printData();
}

void loop() {
    // Empty loop
}
