/*
** EPITECH PROJECT, 2022
** piscine_CPP
** File description:
** sysinfo
*/

#ifndef IMONITORMODULE_HPP_
    #define IMONITORMODULE_HPP_
    #include <string>
    #include <sys/utsname.h>
    #include <pwd.h>
    #include <iostream>
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <fstream>
    #include <string>
    #include <thread>
    #include <exception>

    #define MAXHOSTNAMELEN 253

class IMonitorModule {
    public:
        virtual ~IMonitorModule() = default;
};


class SysInfo {
    private:
        // mettre les variable dedans et faire des get et set
    public:
        SysInfo();
        ~SysInfo();
        void refresh_cpu_info();
        std::string _username;
        std::string _hostname;
        std::string _time;

        utsname _os;

        void refresh_data();

        class Ram : public IMonitorModule {
            public:
                Ram();
                void get_ram_info();
                size_t _totalRam;
                size_t _freeRam;
                size_t _totalSwap;
                size_t _freeSwap;
                std::string RamUsagePercent();
                std::string SwapUsagePercent();
        } _ram;

        class Cpu : public IMonitorModule {
            public:
                Cpu();
                void get_cpu_info();
                std::string _CpuName;
                size_t _CoreNb;
                size_t _ThreadNb;
                class CpuInfo
                {
                    public:
                        size_t previous_idle_time[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                        size_t previous_total_time[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                        size_t idle_time[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                        size_t total_time[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                        std::string cpu_info[32];
                }_cpuinfo;
        } _cpu;

        class Network : public IMonitorModule {
            public:
                Network();
                std::string _receive_bytes = "";
                std::string _receive_packet = "";
                std::string _transmit_bytes = "";
                std::string _transmit_packet = "";
                void count_packets_and_bytes();
        }_network;
};

std::string clean_line(const std::string& line);
std::string get_name(void);
std::string get_time(void);

#endif /* !IMONITORMODULE_HPP_ */
