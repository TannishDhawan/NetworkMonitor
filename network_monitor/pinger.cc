#include "pinger.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include <netinet/ip_icmp.h> 

// Function to calculate checksum
unsigned short checksum(void *b, int len) {
    unsigned short *buf = (unsigned short *)b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

PingResult Pinger::sendPing(const std::string& targetHost) {
    PingResult result;
    result.success = false;
    result.rtt = 0.0;

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        std::cerr << "Error creating socket: " << strerror(errno) << std::endl;
        return result;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, targetHost.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        close(sockfd);
        return result;
    }

    struct icmp icmp_header;
    memset(&icmp_header, 0, sizeof(icmp_header));
    icmp_header.icmp_type = ICMP_ECHO;
    icmp_header.icmp_code = 0;
    icmp_header.icmp_id = getpid();
    icmp_header.icmp_seq = 1;

    // Calculate checksum
    icmp_header.icmp_cksum = 0;
    icmp_header.icmp_cksum = checksum(&icmp_header, sizeof(icmp_header));

    char packet[sizeof(struct icmp)];
    memcpy(packet, &icmp_header, sizeof(struct icmp));

    clock_t start_time = clock();
    if (sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error sending packet: " << strerror(errno) << std::endl;
        close(sockfd);
        return result;
    }

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(sockfd, &fds);
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    if (select(sockfd + 1, &fds, NULL, NULL, &timeout) == 1) {
        socklen_t addr_len = sizeof(server_addr);
        char recv_buffer[1024];
        ssize_t bytes_received = recvfrom(sockfd, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr*)&server_addr, &addr_len);
        if (bytes_received < 0) {
            std::cerr << "Error receiving packet: " << strerror(errno) << std::endl;
            close(sockfd);
            return result;
        }

        clock_t end_time = clock();
        result.rtt = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;
        result.success = true;
    } else {
        std::cerr << "Request timed out" << std::endl;
    }

    close(sockfd);
    return result;
}