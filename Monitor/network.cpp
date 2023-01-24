/*
** EPITECH PROJECT, 2022
** B-PDG-300-PAR-3-1-PDGRUSH3-zacharie.lawson
** File description:
** network
*/

#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IMonitorModule.hpp"

std::string get_wl_line()
{
    std::ifstream file("/proc/net/dev");
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.rfind("wl", 0) == 0)
                break;
        }
    }
    file.close();
    return (line);
}

void SysInfo::Network::count_packets_and_bytes()
{
    int i = 2;
    std::string line = get_wl_line();

    //receive
    for (; line[i] != ' '; i++);
    i++;
    for (; line[i] != ' '; _receive_bytes += line[i], i++);
    for (; line[i] == ' '; i++);
    for (; line[i] != ' '; _receive_packet += line[i], i++);


    //go to transmit
    for (; line[i] == ' ' || line[i] == '0'; i++);

    //transmit
    for (; line[i] != ' '; _transmit_bytes += line[i], i++);
    for (; line[i] == ' '; i++);
    for (; line[i] != ' '; _transmit_packet += line[i], i++);
}
