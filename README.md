# NetworkMonitor


Network Monitor 🌐

Overview - 
Network Monitor is a powerful, real-time network monitoring tool that provides essential metrics for network performance analysis. Built with C++, it offers a clean terminal-based UI and precise measurements of network latency, packet loss, and jitter.


Features ⭐

Real-time Ping Monitoring: Continuous ping measurements to specified targets
Key Performance Metrics:
Round-Trip Time (RTT),
Average Latency,
Packet Loss Percentage,
Network Jitter,
Clean Terminal UI: Using ncurses for a professional, easy-to-read interface,
Low Resource Consumption: Optimized for minimal system impact.

Prerequisites 📋

To build and run Network Monitor, you'll need:
C++ Compiler (GCC 4.8+ or equivalent),
Linux-based Operating System,
NCurses Library,
Root privileges (for ICMP packets).


Usage 🚀

Launch the program with root privileges:

sudo ./network_monitor

The default target is set to Google's DNS (8.8.8.8). To monitor a different host, you can modify the targetHost variable in main.cc.


Press Ctrl+C to exit the program.


Technical Details 🔧

Pinger Class: Handles ICMP echo requests/replies

Metrics Class: Calculates network statistics

GUI Class: Manages the ncurses-based user interface

Error Handling: Robust error checking for network operations

Performance: Optimized for minimal system resource usage
