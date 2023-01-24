/*
** EPITECH PROJECT, 2022
** B-PDG-300-PAR-3-1-PDGRUSH3-zacharie.lawson
** File description:
** sysinfo
*/

#include "./IMonitorModule.hpp"

std::string get_time(void)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    return dt;
}

int get_local_hostname(std::string& hostname)
{
    try
    {
        char temp[MAXHOSTNAMELEN];
        if (gethostname(temp,MAXHOSTNAMELEN) == -1)
        {
            return 84;
        }
        temp[MAXHOSTNAMELEN-1] = '\0';
        hostname = temp;
    } catch (const std::exception &e)
    {
        return 84;
    }
    return 0;
}

std::string get_name(void)
{
    uid_t uid;
    struct passwd *pw;

    uid = geteuid ();
    pw = getpwuid (uid);
    if (pw) {
      return pw->pw_name;
    }
    return std::string("");
}

SysInfo::~SysInfo()
{
}

SysInfo::SysInfo()
{
    _username = get_name();
    get_local_hostname(_hostname);
    _time = get_time();
    uname(&_os);

}

void SysInfo::refresh_data()
{
    _network._receive_bytes = "";
    _network._receive_packet = "";
    _network._transmit_packet = "";
    _network._transmit_bytes = "";
    refresh_cpu_info();
    _time = get_time();
    _ram.get_ram_info();
    //_network.count_packets_and_bytes();
}

SysInfo::Cpu::Cpu()
{
    get_cpu_info();
}

SysInfo::Ram::Ram()
{
    get_ram_info();
}

SysInfo::Network::Network()
{
    //count_packets_and_bytes();
}


