# NetworkMonitor


NetworkMonitor
Network Monitor 🌐

Overview - Network Monitor is a powerful, real-time network monitoring tool that provides essential metrics for network performance analysis. Built with C++, it offers a clean terminal-based UI and precise measurements of network latency, packet loss, and jitter.


How Does It Work -

The program monitors network performance by repeatedly pinging a target host (e.g., 8.8.8.8 ,which i am using right now ) and calculating metrics like latency, packet loss, and jitter. The Pinger class sends ICMP echo requests and calculates round-trip time (RTT). Results are passed to the Metrics class, which tracks RTT values, computes average latency, packet loss, and jitter. The GUI uses ncurses to display real-time statistics. The main function combines these components into a continuous loop, pinging the target every second and updating the GUI with the latest stats. You can now monitor the network in real-time and terminate the program with Ctrl+C.

Features ⭐

Real-time Ping Monitoring: Continuous ping measurements to specified targets Key Performance Metrics: Round-Trip Time (RTT), Average Latency, Packet Loss Percentage, Network Jitter, Clean Terminal UI: Using ncurses, easy-to-read interface, Low Resource Consumption: Optimized for minimal system impact.

Prerequisites 📋

To build and run Network Monitor, you'll need: C++ Compiler (GCC 4.8+ or equivalent), Linux-based Operating System, NCurses Library, Root privileges (for ICMP packets).

Usage 🚀

Launch the program with root privileges:

sudo ./network_monitor

The default target is set to Google's DNS (8.8.8.8). To monitor a different host, you can modify the targetHost variable in main.cc.

