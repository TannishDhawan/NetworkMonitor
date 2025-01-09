// database.cpp
#include "Database.h"
#include <iostream>

Database::Database(const string& name) : db_name(name) {
    int rc = sqlite3_open(db_name.c_str(), &db);
    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return;
    }
    initializeDatabase();
}

Database::~Database() {
    sqlite3_close(db);
}

void Database::initializeDatabase() {
    const char* sql = "CREATE TABLE IF NOT EXISTS network_metrics (""id INTEGER PRIMARY KEY AUTOINCREMENT,""timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,""target_host TEXT,""rtt REAL,""avg_latency REAL,""packet_loss REAL,""jitter REAL);";
    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

void Database::storeMetrics(const string& target_host, double rtt, double avg_latency, double packet_loss, double jitter) {
    string sql = "INSERT INTO network_metrics (target_host, rtt, avg_latency, packet_loss, jitter) ""VALUES ('" + target_host + "', " + to_string(rtt) + ", " +to_string(avg_latency) + ", " +to_string(packet_loss) + ", " +to_string(jitter) + ");";
    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}
void Database::displayLastRecords(int limit) {
    string sql = "SELECT * FROM network_metrics ORDER BY timestamp DESC LIMIT " + to_string(limit) + ";";
    
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "\nLast " << limit << " records:\n";
    cout << "Timestamp | Target | RTT | Avg Latency | Packet Loss | Jitter\n";
    cout << "--------------------------------------------------------\n";
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << sqlite3_column_text(stmt, 1) << " | "  // timestamp
             << sqlite3_column_text(stmt, 2) << " | "  // target_host
             << sqlite3_column_double(stmt, 3) << " | " // rtt
             << sqlite3_column_double(stmt, 4) << " | " // avg_latency
             << sqlite3_column_double(stmt, 5) << " | " // packet_loss
             << sqlite3_column_double(stmt, 6) << endl; // jitter
    }
    
    sqlite3_finalize(stmt);
}

void Database::clearDatabase() {
    const char* sql = "DELETE FROM network_metrics;";
    char* errMsg = 0;
    
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error clearing database: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Database cleared successfully\n";
    }
}