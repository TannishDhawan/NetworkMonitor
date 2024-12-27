#include "metrics.h"
#include <numeric>
#include <cmath>

void Metrics::update(const PingResult& result) {
    if (result.success) {
        rtt_values.push_back(result.rtt);
    }
    total_packets++;
    if (!result.success) {
        lost_packets++;
    }
}

double Metrics::getAverageLatency() const {
    if (rtt_values.empty()) return 0.0;
    return std::accumulate(rtt_values.begin(), rtt_values.end(), 0.0) / rtt_values.size();
}

double Metrics::getPacketLossPercentage() const {
    if (total_packets == 0) return 0.0;
    return (static_cast<double>(lost_packets) / total_packets) * 100;
}

double Metrics::getJitter() const {
    if (rtt_values.size() < 2) return 0.0;
    double sum = 0.0;
    double avg = getAverageLatency();
    for (double rtt : rtt_values) {
        sum += std::abs(rtt - avg);
    }
    return sum / rtt_values.size();
}