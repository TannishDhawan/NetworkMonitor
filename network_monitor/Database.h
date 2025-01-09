// database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include "pinger.h"
using namespace std;
class Database {
public:
    Database(const string& db_name);
    ~Database();
    void storeMetrics(const string& target_host, double rtt, double avg_latency, double packet_loss, double jitter);
    void initializeDatabase();
    void displayLastRecords(int limit = 5);
    void clearDatabase();

private:
    sqlite3* db;
    string db_name;
};

#endif