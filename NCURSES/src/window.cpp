/*
** EPITECH PROJECT, 2022
** B-PDG-300-PAR-3-1-PDGRUSH3-zacharie.lawson
** File description:
** window
*/

#include <ncurses.h>
#include "../../Monitor/IMonitorModule.hpp"
#include "../include/Text.hpp"
#include <string>

int print_in_cpu(Window &window, SysInfo &core)
{
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);

    mvwprintw(window.cpu_box, 1, 1, ("Cpu name : " + core._cpu._CpuName).c_str());
    mvwprintw(window.cpu_box, 3, 1, ("Core number : " + std::to_string(core._cpu._CoreNb)).c_str());
    mvwprintw(window.cpu_box, 5, 1, ("Thread number : " + std::to_string(core._cpu._ThreadNb)).c_str());
    for (size_t i = 1; i < (core._cpu._ThreadNb + 1); i++) {
        std::string temp = core._cpu._cpuinfo.cpu_info[i];
        try {
            int res = int(stof(temp)/ (100/3)) + 1;
            wattron(window.cpu_box, COLOR_PAIR(res));
            mvwprintw(window.cpu_box, 5 + (i * 2), 1, ("Cpu " + std::to_string(i) + " : " +  temp.substr(0, (3 + temp.find_first_of(".", 0))) + "%%").c_str());
            wattroff(window.cpu_box, COLOR_PAIR(res));
        } catch (std::exception &e) {
            mvwprintw(window.cpu_box, 5 + (i * 2), 1, ("Cpu " + std::to_string(i) + " : " +  temp.substr(0, (3 + temp.find_first_of(".", 0))) + "%%").c_str());
        }
    }
    std::string temp = core._cpu._cpuinfo.cpu_info[0];
    try {
        int res = int(stof(temp)/ (100/3)) + 1;
        wattron(window.cpu_box, COLOR_PAIR(res));
        mvwprintw(window.cpu_box, 5 + (core._cpu._ThreadNb * 2), 1, ("Cpu average : " +  temp.substr(0, (3 + temp.find_first_of(".", 0))) + "%%").c_str());
        wattroff(window.cpu_box, COLOR_PAIR(res));
    } catch (std::exception &e) {
        mvwprintw(window.cpu_box, 5 + (core._cpu._ThreadNb * 2), 1, ("Cpu average : " +  temp.substr(0, (3 + temp.find_first_of(".", 0))) + "%%").c_str());
    }

    return 0;
}

int print_in_ram(Window &window, SysInfo &core)
{
    mvwprintw(window.ram_box, 1, 1, ("totalRam : " + std::to_string(core._ram._totalRam)).c_str());
    mvwprintw(window.ram_box, 3, 1, ("freeRam : " + std::to_string(core._ram._freeRam)).c_str());
    std::string temp = core._ram.RamUsagePercent();
    mvwprintw(window.ram_box, 5, 1, ("Ram usage : " +  temp.substr(0, (3 + temp.find_first_of(".", 0))) + "%%").c_str());
    mvwprintw(window.ram_box, 7, 1, ("totalSwap : " + std::to_string(core._ram._totalSwap)).c_str());
    mvwprintw(window.ram_box, 9, 1, ("freeSwap : " + std::to_string(core._ram._freeSwap)).c_str());
    temp = core._ram.SwapUsagePercent();
    mvwprintw(window.ram_box, 11, 1, ("Swap usage : " +  temp.substr(0, (3 + temp.find_first_of(".", 0))) + "%%").c_str());
    return 0;
}

int print_in_network(Window &window, SysInfo &core)
{
    mvwprintw(window.network_box, 1, 1, ("Receive packets : " + core._network._receive_packet).c_str());
    mvwprintw(window.network_box, 3, 1, ("Receive bytes : " + core._network._receive_bytes).c_str());
    mvwprintw(window.network_box, 5, 1, ("Transmit bytes : " + core._network._transmit_bytes).c_str());
    mvwprintw(window.network_box, 7, 1, ("Transmit packets : " + core._network._transmit_packet).c_str());

    return 0;
}

int print_in_system(Window &window, SysInfo &core)
{
    mvwprintw(window.sysinfo_box, 1, 1, ("Username : " + core._username).c_str());
    mvwprintw(window.sysinfo_box, 3, 1, ("Hostname : " + core._hostname).c_str());
    mvwprintw(window.sysinfo_box, 5, 1, ("Time : " + core._time).c_str());
    mvwprintw(window.sysinfo_box, 7, 1, ("Os : " + std::string(core._os.sysname)).c_str());
    mvwprintw(window.sysinfo_box, 9, 1, ("Version : " + std::string(core._os.version)).c_str());
    mvwprintw(window.sysinfo_box, 11, 1, ("Release : " + std::string(core._os.release)).c_str());

    return 0;
}

int init_window(Window &window)
{
    noecho();
    curs_set(0);

    init_pair(3, COLOR_RED, COLOR_BLACK);
    wattron(window.cpu_box,COLOR_PAIR(3));
    wattron(window.ram_box,COLOR_PAIR(3));
    wattron(window.sysinfo_box,COLOR_PAIR(3));
    wattron(window.network_box,COLOR_PAIR(3));
    box(window.cpu_box, 0, 0);
    box(window.ram_box, 0, 0);
    box(window.sysinfo_box, 0, 0);
    box(window.network_box, 0, 0);
    wattroff(window.cpu_box,COLOR_PAIR(3));
    wattroff(window.ram_box,COLOR_PAIR(3));
    wattroff(window.sysinfo_box,COLOR_PAIR(3));
    wattroff(window.network_box,COLOR_PAIR(3));
    mvwprintw(window.cpu_box, 0, 10, "CPU");
    mvwprintw(window.ram_box, 0, 10, "RAM");
    mvwprintw(window.sysinfo_box, 0, 10, "SYSTEM");
    mvwprintw(window.network_box, 0, 10, "NETWORK");

    return 0;
}

int text(SysInfo &core)
{
    initscr();
    Window window;
    start_color();

    window.cpu_box = newwin(LINES - 1, COLS / 2, 0, 0);
    window.sysinfo_box = newwin(LINES / 2, COLS / 2, 0, COLS / 2);
    window.network_box = newwin(LINES / 2, COLS / 4, LINES / 2, COLS * 3 / 4);
    window.ram_box = newwin(LINES / 2, COLS / 4, LINES / 2, COLS / 2);

    refresh();
    init_window(window);
    char stopLoop = 'a';
    while(1) {
        timeout(0);
        stopLoop = getch();
        if (stopLoop == 'q') {
            endwin();
            return 0;
        }
        core.refresh_data();
        wclear(window.cpu_box);
        wclear(window.ram_box);
        wclear(window.sysinfo_box);
        wclear(window.network_box);
        print_in_system(window, core);
        print_in_network(window, core);
        print_in_ram(window, core);
        print_in_cpu(window, core);
        init_window(window);
        wrefresh(window.cpu_box);
        wrefresh(window.ram_box);
        wrefresh(window.sysinfo_box);
        wrefresh(window.network_box);
        clear();
        sleep(1);
        refresh();
    }
    endwin();
    return 0;
}
