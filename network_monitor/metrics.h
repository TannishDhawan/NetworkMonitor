#ifndef METRICS_H
#define METRICS_H

#include <vector>
#include "pinger.h" 

class Metrics {
private:
    std::vector<double> rtt_values;
    int total_packets;
    int lost_packets;

public:
    Metrics() : total_packets(0), lost_packets(0) {}

    void update(const PingResult& result);
    double getAverageLatency() const;
    double getPacketLossPercentage() const;
    double getJitter() const;
};

#endif // METRICS_H