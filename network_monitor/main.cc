#include <iostream>
#include <thread>
#include <chrono>
#include "pinger.h"
#include "metrics.h"
#include "gui.h"
#include "Database.h"
using namespace std;

int main() {
    string targetHost = "8.8.8.8";// you can change this to any host you want to ping
    cout << "to cancel the program press ctrl+c" << endl;
    Pinger pinger;
    Metrics metrics;
    Database db("network_monitor.db");

    //Testing 
    cout << "\n--- Extended Database Testing ---" << endl;
    db.storeMetrics("test", .50, 0.3, 0, 0.04);
    cout << "\nDisplaying last 5 records after multiple insertions:" << endl;
    db.displayLastRecords();


    cout << "\nClearing database..." << endl;
    db.clearDatabase();

    cout << "\nDisplaying records after clearing: should be empty" << endl;
    db.displayLastRecords(); // Should be empty

    cout<<"\n--- End Database Testing ---"<<endl;

    init_gui();

    bool running = true;
    while (running) {
        PingResult result = pinger.sendPing(targetHost);

        metrics.update(result);

        double avgLatency = metrics.getAverageLatency();
        double packetLoss = metrics.getPacketLossPercentage();
        double jitter = metrics.getJitter();

        db.storeMetrics(targetHost,result.success ? result.rtt : -1,avgLatency,packetLoss,jitter);
        update_gui(targetHost, result.success ? result.rtt : -1, avgLatency, packetLoss, jitter);

        this_thread::sleep_for(chrono::seconds(1));
    }

    cleanup_gui();
    return 0;
}