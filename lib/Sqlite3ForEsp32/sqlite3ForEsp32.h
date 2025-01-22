#ifndef SQLITE3FORESP32_H
#define SQLITE3FORESP32_H

#include <sqlite3.h>
#include <SPIFFS.h>
#include <Arduino.h>

class SQLite3ForEsp32 {
public:
    SQLite3ForEsp32(const char *dbPath);
    ~SQLite3ForEsp32();

    void initializeSPIFFS();
    bool executeSQL(const char *sql, sqlite3_callback callback = nullptr, void *data = nullptr);
    void createTable();
    void addData(const char *value);
    void printData();
    void deleteRow(int id);
    void updateRow(int id, const char *newValue);

private:
    sqlite3* openDatabase();
    void closeDatabase();

    const char *databasePath;
    sqlite3 *db;
};

#endif // SQLITE3FORESP32_H
