/*
** EPITECH PROJECT, 2022
** Text.hpp
** File description:
** Text
*/

#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#include <curses.h>
#include <iostream>
#include "../../SFML/Gui.hpp"

class Window : public IMonitorDisplay {
    public:
        WINDOW *cpu_box;
        WINDOW *sysinfo_box;
        WINDOW *network_box;
        WINDOW *ram_box;
};

int text(SysInfo &core);

#endif /*_TEXT_HPP_*/