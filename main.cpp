#include <string>
#include <iostream>
#include "Monitor/IMonitorModule.hpp"
#include "SFML/Gui.hpp"
#include "NCURSES/include/Text.hpp"

int main(int ac, char **av)
{
    std::string strr;
    SysInfo core;
    if ((ac == 2) && av[1][0] == '-' && av[1][1] == 'h') {
        std::cout << "USAGE:\n\n./MyGKrellm -g   \"To launch graphics interface.\"\n";
        std::cout << "  Controles:\n        C Key to mute and unmute cpu info\n";
        std::cout << "        R Key to mute and unmute ram info\n";
        std::cout << "        S Key to mute and unmute swap info\n";
        std::cout << "        N Key to mute and unmute network info\n";
        std::cout << "        G Key to mute and unmute Graphics\n";
        std::cout << "        P Key to mute and unmute pourcentage cpu activity\n";
        std::cout << "./MyGKrellm -n     \"To launch in ncurses.\"\n";
        return 0;
    } else if (ac >= 2 && std::string(av[1]) == "-g") {
        std::cout << "Graphical mode" << std::endl;
        Gui Data(core);
        Data.Graphical(core);
        return 0;
    } else if ((ac == 2) && std::string(av[1]) == "-n") {
        std::cout << "Text mode" << std::endl;
        text(core);
        return 0;
    }
    std::cout << "username " << core._username << std::endl;
    std::cout << "hostname " << core._hostname << std::endl;
    std::cout << "time " << core._time << std::endl;
    std::cout << "os:" << std::endl;
    std::cout << "\tsystem name " << core._os.sysname << std::endl;
    std::cout << "\tsystem version " << core._os.version << std::endl;
    std::cout << "\tsystem release " << core._os.release << std::endl;
    std::cout << "ram:" << std::endl;
    std::cout << "\ttotal ram " << core._ram._totalRam << std::endl;
    std::cout << "\tfree ram " << core._ram._freeRam << std::endl;
    std::cout << "\ttotal swap " << core._ram._totalSwap << std::endl;
    std::cout << "\tfree swap " << core._ram._freeSwap << std::endl;
    std::cout << "cpu:" << std::endl;
    std::cout << "\tcpu model " << core._cpu._CpuName << std::endl;
    std::cout << "\tcpu core number " << core._cpu._CoreNb << std::endl;
    std::cout << "\tcpu thread number " << core._cpu._ThreadNb << std::endl;
    core._network.count_packets_and_bytes();
    std::cout << "network:" << std::endl;
    std::cout << "\treceive_bytes " << core._network._receive_bytes << std::endl;
    std::cout << "\treceive_packet " << core._network._receive_packet << std::endl;
    std::cout << "\ttransmit_bytes " << core._network._transmit_bytes << std::endl;
    std::cout << "\ttransmit_packet " << core._network._transmit_packet << std::endl;
    std::cout << "ram percent: " << core._ram.RamUsagePercent() << std::endl;
    std::cout << "swap percent: " << core._ram.SwapUsagePercent() << std::endl;
    sleep(1);
    core.refresh_data();
    std::cout << "cpu percent: " << core._cpu._cpuinfo.cpu_info[0] << std::endl;
    return 0;
}