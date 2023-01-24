/*
** EPITECH PROJECT, 2022
** piscine_CPP
** File description:
** test
*/

#include "IMonitorModule.hpp"

void SysInfo::Ram::get_ram_info()
{
    std::ifstream cpufile("/proc/meminfo");
    std::string line;

    if (cpufile.is_open()) {
        while (std::getline(cpufile, line)) {
            std::string token = clean_line(line.substr(line.find(':') + 1));
            if (line.rfind("MemTotal", 0) == 0) {
                _totalRam = std::stoi(token);
            }
            if (line.rfind("MemFree", 0) == 0)
                _freeRam = std::stoi(token);
            if (line.rfind("SwapTotal", 0) == 0)
                _totalSwap = std::stoi(token);
            if (line.rfind("SwapFree", 0) == 0)
                _freeSwap = std::stoi(token);
        }
    }
    cpufile.close();
}

std::string SysInfo::Ram::RamUsagePercent()
{
    return (std::to_string(100 * (static_cast<double>(_totalRam - _freeRam) / static_cast<double>(_totalRam))) + "%");
}

std::string SysInfo::Ram::SwapUsagePercent()
{
    return (std::to_string(100 * (static_cast<double>(_totalSwap - _freeSwap) / static_cast<double>(_totalSwap))) + "%");

}