/*
** EPITECH PROJECT, 2022
** piscine_CPP
** File description:
** test
*/

#include "IMonitorModule.hpp"
#include <sstream>
#include <vector>
#include <fstream>
#include <limits>
#include <numeric>

void SysInfo::Cpu::get_cpu_info()
{
    std::ifstream cpufile("/proc/cpuinfo");
    std::string delim = ":";
    std::string line;

    if (cpufile.is_open()) {
        while (std::getline(cpufile, line)) {
            std::string token = line.substr(line.find(':') + 1);
            if (line.rfind("model name", 0) == 0)
                _CpuName = token;
            if (line.rfind("siblings", 0) == 0)
                _ThreadNb = std::stoi(token);
            if (line.rfind("cpu cores", 0) == 0)
                _CoreNb = std::stoi(token);
        }
    }
    cpufile.close();
}

static std::vector<size_t> get_cpu_times(size_t pos) {
    std::ifstream proc_stat("/proc/stat");
    proc_stat.seekg(std::ios::beg);
    for(size_t i = 0; i < pos; i += 1)
        proc_stat.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    proc_stat.ignore(5, ' ');
    std::vector<size_t> times;
    for (size_t time; proc_stat >> time; times.push_back(time));
    return times;
}

static bool get_cpu_times(size_t &idle_time, size_t &total_time, size_t pos) {
    const std::vector<size_t> cpu_times = get_cpu_times(pos);
    if (cpu_times.size() < 4)
        return false;
    idle_time = cpu_times[3];
    total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);
    return true;
}

void SysInfo::refresh_cpu_info()
{
    for (size_t i = 0; i < (this->_cpu._ThreadNb + 1); i += 1) {
        if (!get_cpu_times(this->_cpu._cpuinfo.idle_time[i], this->_cpu._cpuinfo.total_time[i], (i)))
            break;
        const float idle_time_delta = this->_cpu._cpuinfo.idle_time[i] - this->_cpu._cpuinfo.previous_idle_time[i];
        const float total_time_delta = this->_cpu._cpuinfo.total_time[i] - this->_cpu._cpuinfo.previous_total_time[i];
        const float utilization = 100.0 * (1.0 - idle_time_delta / total_time_delta);
        std::string temp = (std::to_string(utilization) + " %");
        this->_cpu._cpuinfo.cpu_info[i] = temp.substr(0, (3 + temp.find_first_of(".", 0)));
        this->_cpu._cpuinfo.previous_idle_time[i] = this->_cpu._cpuinfo.idle_time[i];
        this->_cpu._cpuinfo.previous_total_time[i] = this->_cpu._cpuinfo.total_time[i];
    }
}