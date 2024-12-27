#include "gui.h"
#include <ncurses.h>
#include <string>
#include <iostream>

using namespace std;

void init_gui() {
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
}

void update_gui(const string& target_host, double current_rtt, double avg_latency, double packet_loss, double jitter) {
    clear();
    mvprintw(0, 0, ("Network Monitor - Target: " + target_host).c_str());
    mvprintw(1,0,(" to exit the program press ctrl+c"));
    mvprintw(2, 0, "----------------------------------------");
    mvprintw(3, 0, ("Current RTT: " + (current_rtt >= 0 ? to_string(current_rtt) + " ms" : "N/A")).c_str());
    mvprintw(4, 0, ("Average RTT: " + to_string(avg_latency) + " ms").c_str());
    mvprintw(5, 0, ("Packet Loss: " + to_string(packet_loss) + "%").c_str());
    mvprintw(6, 0, ("Jitter: " + to_string(jitter) + " ms").c_str());
    refresh();
}

void cleanup_gui() {
    endwin();
}