#ifndef GUI_H
#define GUI_H

#include <string>

void init_gui();
void update_gui(const std::string& target_host, double current_rtt, double avg_latency, double packet_loss, double jitter);
void cleanup_gui();

#endif // GUI_H