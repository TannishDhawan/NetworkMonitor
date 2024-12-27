#include <iostream>
#include <thread>
#include <chrono>
#include "pinger.h"
#include "metrics.h"
#include "gui.h"

int main() {
    // Initialize the target host (you can modify this to any IP or hostname)
    std::string targetHost = "8.8.8.8";// using Google's public DNS server (You can use your own IP address) 
    std::cout<<"to cancel the program press ctrl+c"<<std::endl;
    Pinger pinger;
    Metrics metrics;
    init_gui();

    // Main loop for monitoring
    bool running = true;
    while (running) {
        PingResult result = pinger.sendPing(targetHost);

        // Update metrics with the result
        metrics.update(result);

        // Get the latest statistics
        double avgLatency = metrics.getAverageLatency();
        double packetLoss = metrics.getPacketLossPercentage();
        double jitter = metrics.getJitter();

        // Update the GUI with the latest metrics
        update_gui(targetHost, result.success ? result.rtt : -1, avgLatency, packetLoss, jitter);

        // Wait for 1 second before the next ping
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Cleanup the GUI before exiting
    cleanup_gui();

    return 0;
}