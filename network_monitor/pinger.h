#ifndef PINGER_H
#define PINGER_H

#include <string>

struct PingResult {
    bool success;
    double rtt; // Round-trip time in milliseconds
};

class Pinger {
public:
    PingResult sendPing(const std::string& targetHost);
};

#endif // PINGER_H