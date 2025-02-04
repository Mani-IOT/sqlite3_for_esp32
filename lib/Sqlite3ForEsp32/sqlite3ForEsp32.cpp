#include "sqlite3ForEsp32.h"

// Constructor
SQLite3ForEsp32::SQLite3ForEsp32(const char *dbPath) : databasePath(dbPath), db(nullptr) {}

// Destructor
SQLite3ForEsp32::~SQLite3ForEsp32() {
    if (db) {
        closeDatabase();
    }
}

// Initialize SPIFFS
void SQLite3ForEsp32::initializeSPIFFS() {
    if (!SPIFFS.begin(true)) {
        Serial.println("Failed to mount SPIFFS. Formatting...");
        if (!SPIFFS.format()) {
            Serial.println("SPIFFS formatting failed. Halting.");
            while (true); // Stop execution
        }
        Serial.println("SPIFFS formatted successfully.");
    } else {
        Serial.println("SPIFFS mounted successfully.");
    }
}

// Open the database
sqlite3* SQLite3ForEsp32::openDatabase() {
    int rc = sqlite3_open(databasePath, &db);
    if (rc != SQLITE_OK) {
        Serial.printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return nullptr;
    }
    //Serial.println("Database opened successfully.");
    return db;
}

// Close the database
void SQLite3ForEsp32::closeDatabase() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
        Serial.println("Database closed.");
    }
}

// Execute an SQL query
bool SQLite3ForEsp32::executeSQL(const char *sql, sqlite3_callback callback, void *data) {
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, callback, data, &errMsg);
    if (rc != SQLITE_OK) {
        Serial.printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

// Create table if it doesn't exist
void SQLite3ForEsp32::createTable() {
    if (!openDatabase()) return;

    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);";
    if (executeSQL(sql)) {
        Serial.println("Table created successfully or already exists.");
    }

    closeDatabase();
}

// Add data to the database
void SQLite3ForEsp32::addData(const char *value) {
    if (!openDatabase()) return;

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO test (value) VALUES ('%s');", value);
    if (executeSQL(sql)) {
        Serial.println("Data inserted successfully.");
    }

    closeDatabase();
}

// Print data from the database
void SQLite3ForEsp32::printData() {
    if (!openDatabase()) return;

    const char *sql = "SELECT * FROM test;";
    auto callback = [](void *data, int argc, char **argv, char **azColName) -> int {
//        Serial.println("Row:");
        for (int i = 0; i < argc; i++) {
            Serial.printf("\n  %s, %s", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        return 0;
    };

    if (executeSQL(sql, callback)) {
        Serial.println("Data fetched successfully.");
    }

    closeDatabase();
}

// Delete a row by ID
void SQLite3ForEsp32::deleteRow(int id) {
    if (!openDatabase()) return;

    char sql[128];
    snprintf(sql, sizeof(sql), "DELETE FROM test WHERE id = %d;", id);
    if (executeSQL(sql)) {
        Serial.printf("Row with ID %d deleted successfully.\n", id);
    }

    closeDatabase();
}

// Update a row by ID
void SQLite3ForEsp32::updateRow(int id, const char *newValue) {
    if (!openDatabase()) return;

    char sql[256];
    snprintf(sql, sizeof(sql), "UPDATE test SET value = '%s' WHERE id = %d;", newValue, id);
    if (executeSQL(sql)) {
        Serial.printf("Row with ID %d updated successfully to '%s'.\n", id, newValue);
    }

    closeDatabase();
}
