/*
** EPITECH PROJECT, 2022
** rush03
** File description:
** Gui
*/

#include "Gui.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/GpuPreference.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Font.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "../Monitor/IMonitorModule.hpp"
#include <string.h>
#include <fstream>
#include <iostream>
#include <numeric>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <limits>

Gui::Gui(const SysInfo &system): _window (sf::VideoMode(1200, (675)), "MyGKrellm")
{
    //this->back.loadFromFile((std::string)"assets/cu.jpg");
    //this->wallpaper.setTexture(this->back);
    this->_event.key.code = sf::Keyboard::A;
    this->wallpaper.setScale(sf::Vector2f{0.5, 0.5});
    this->_screen_height = 675;
    this->_screen_width = 1200;
    this->_window_title = "MyGKrellm";
    this->_width_mini_box = 0;
    this->_height_mini_box= 0;
    this->_window.setFramerateLimit(60);
    this->GraphLinkedListLen = 0;
    this->GraphLinkedListLenSwap = 0;
    this->GraphLinkedListLenRam = 0;
    this->_my_Ram = nullptr;
    this->_my_Swap = nullptr;
    for (size_t i = 0; i < (system._cpu._ThreadNb + 1); i += 1)
        this->_GraphLinkedList[i] = nullptr;
}

Gui::~Gui()
{
    ;
}

int Gui::getscreenWidth() const
{
    return this->_screen_width;
}

int Gui::getscreenHeight() const
{
    return this->_screen_height;
}

std::string Gui::getscreenWindowTitle() const
{
    return this->_window_title;
}

void Gui::print_text(sf::RenderWindow &window, sf::Text contener, std::string text, sf::Vector2f pos)
{
    contener.setPosition(pos);
    contener.setString(text);
    window.draw(contener);
}

void Gui::display_value(SysInfo system)
{
    sf::Font myFont;
    myFont.loadFromFile("assets/Agency_FB.ttf");
    sf::Text pourcentage("empty", myFont, 25);
    pourcentage.setOutlineThickness(1);
    pourcentage.setOrigin(sf::Vector2f{15, 15});
    pourcentage.setFillColor(sf::Color::Cyan);

    for (size_t i = 0; i < system._cpu._ThreadNb; i += 1) {
        print_text(this->_window, pourcentage, ("Cpu0" + std::to_string(i + 1)) + ":", (sf::Vector2f){(this->_width_mini_box / 2), ((this->_height_mini_box * (float)i) + (11 * (float)i) + (this->_height_mini_box / 2) + 1)});
        print_text(this->_window, pourcentage, system._cpu._cpuinfo.cpu_info[(i + 1)] + " %", (sf::Vector2f){(this->_width_mini_box / 2), ((this->_height_mini_box * (float)i) + (11 * (float)i) + (this->_height_mini_box / 2) + 30)});
    }
    pourcentage.setCharacterSize(60);
    pourcentage.setOrigin(sf::Vector2f{-25, -10});
    print_text(this->_window, pourcentage, "Cpu Average:", (sf::Vector2f){((this->getscreenWidth() / (float)2) / 2) - 50, ((this->getscreenHeight() / (float)2) / 2) - 80});
    print_text(this->_window, pourcentage, system._cpu._cpuinfo.cpu_info[(0)] + " %", (sf::Vector2f){(this->getscreenWidth() / (float)2) / 2, (this->getscreenHeight() / (float)2) / 2});
}

void Gui::display_block(SysInfo system)
{
    sf::RectangleShape rec((sf::Vector2f){320, 180});

    rec.setPosition((sf::Vector2f){10, 10});
    rec.setOutlineColor(sf::Color::Red);
    rec.setFillColor(sf::Color::Transparent);
    rec.setOutlineThickness(2);
    sf::Vector2f temp_size;

    if (system._cpu._ThreadNb >= 4) {
        for (size_t i = 0; i < system._cpu._ThreadNb; i += 1) {
            rec.setSize((sf::Vector2f){((((((this->getscreenHeight() - 20) / (float)system._cpu._ThreadNb) - 10) / (float)9)) * (float)16), (((this->getscreenHeight() - 20) / (float)system._cpu._ThreadNb) - 10)});
            rec.setPosition((sf::Vector2f){10, (((this->getscreenHeight() / system._cpu._ThreadNb) * (float)i) + 10)});
            this->_window.draw(rec);
        }
        this->_width_mini_box = rec.getSize().x;
        this->_height_mini_box = rec.getSize().y;
        rec.setPosition((sf::Vector2f){(float)20 + rec.getSize().x, 10});
        rec.setSize((sf::Vector2f){((this->getscreenWidth() - ((((((this->getscreenHeight() - 20) / (float)system._cpu._ThreadNb) - 10) / (float)9)) * (float)16)) - 30), (this->getscreenHeight() - (float)17)});
        rec.setSize((sf::Vector2f){(rec.getSize().x / 2) - 5, (rec.getSize().y / 2) - 5});
        this->_window.draw(rec);
        rec.setPosition((sf::Vector2f){rec.getPosition().x, ((float)this->getscreenHeight() / 2) + 10});
        this->_window.draw(rec);
        temp_size = rec.getSize();
        rec.setSize((sf::Vector2f){temp_size.x, (temp_size.y / 2)});
        rec.setPosition((sf::Vector2f){rec.getPosition().x, ((float)this->getscreenHeight() / 2) + 10});
        this->_window.draw(rec);
        rec.setSize(temp_size);
        rec.setPosition((sf::Vector2f){rec.getPosition().x + rec.getSize().x + 10, ((float)this->getscreenHeight() / 2) + 10});
        this->_window.draw(rec);
        temp_size = rec.getSize();
        rec.setSize((sf::Vector2f){(temp_size.x / 2) - 20, (temp_size.y / 2) - 20});
        rec.setPosition((sf::Vector2f){rec.getPosition().x + 10, ((float)this->getscreenHeight() / 2) + 20});
        this->_window.draw(rec);
        rec.setPosition((sf::Vector2f){(rec.getPosition().x + 20 + rec.getSize().x), ((float)this->getscreenHeight() / 2) + 20});
        this->_window.draw(rec);
        rec.setPosition((sf::Vector2f){(rec.getPosition().x - 30 - rec.getSize().x), rec.getPosition().y});
        rec.setSize(temp_size);
        rec.setPosition((sf::Vector2f){rec.getPosition().x, 10});
    } else {
        for (size_t i = 0; i < system._cpu._ThreadNb; i += 1) {
            rec.setSize((sf::Vector2f){((((((this->getscreenHeight() - 20) / (float)4) - 10) / (float)9)) * (float)16), (((this->getscreenHeight() - 20) / (float)4) - 10)});
            rec.setPosition((sf::Vector2f){10, (((this->getscreenHeight() / 4) * (float)i) + 10)});
            this->_window.draw(rec);
        }
        this->_width_mini_box = rec.getSize().x;
        this->_height_mini_box = rec.getSize().y;
        rec.setPosition((sf::Vector2f){(float)20 + rec.getSize().x, 10});
        rec.setSize((sf::Vector2f){((this->getscreenWidth() - ((((((this->getscreenHeight() - 20) / (float)4) - 10) / (float)9)) * (float)16)) - 30), (this->getscreenHeight() - (float)17)});
        rec.setSize((sf::Vector2f){(rec.getSize().x / 2) - 5, (rec.getSize().y / 2) - 5});
        this->_window.draw(rec);
        rec.setPosition((sf::Vector2f){rec.getPosition().x, ((float)this->getscreenHeight() / 2) + 10});
        this->_window.draw(rec);
        rec.setPosition((sf::Vector2f){rec.getPosition().x + rec.getSize().x + 10, ((float)this->getscreenHeight() / 2) + 10});
        this->_window.draw(rec);
        rec.setPosition((sf::Vector2f){rec.getPosition().x + rec.getSize().x + 10, 10});
    }
    this->_window.draw(rec);
}

void Gui::del_element(int pos)
{
    GraphLinkedList *temp = this->_GraphLinkedList[pos];
    GraphLinkedList *save = nullptr;
    GraphLinkedList *del;

    for (size_t i = 0; i < (this->GraphLinkedListLen - 1); i++) {
        save = temp;
        temp = temp->next;
    }
    del = temp;
    delete del;
    save->next = temp->next;
}

void Gui::del_element_swap()
{
    GraphLinkedList *temp = this->_my_Swap;
    GraphLinkedList *save = nullptr;
    GraphLinkedList *del;

    for (size_t i = 0; i < (this->GraphLinkedListLenSwap - 1); i++) {
        save = temp;
        temp = temp->next;
    }
    del = temp;
    delete del;
    save->next = temp->next;
};

void Gui::del_element_ram()
{
    GraphLinkedList *temp = this->_my_Ram;
    GraphLinkedList *save = nullptr;
    GraphLinkedList *del;

    for (size_t i = 0; i < (this->GraphLinkedListLenRam - 1); i++) {
        save = temp;
        temp = temp->next;
    }
    del = temp;
    delete del;
    save->next = temp->next;
}

void Gui::add_element_ram(SysInfo system)
{
    GraphLinkedList *node;
    GraphLinkedList *temp;
    sf::Color orange;

    orange.a = 255;
    orange.r = 255;
    orange.b = 0;
    orange.g = 127;
    float tempo = 0;
    node = new GraphLinkedList;
    system.refresh_data();
    tempo = std::atof(system._ram.RamUsagePercent().c_str());
    node->line.setSize(sf::Vector2f{2, (float)(1.43 * (std::atof(system._ram.RamUsagePercent().c_str())))});
    if (tempo == 100)
        node->line.setFillColor(sf::Color::Red);
    else if (tempo >= 50 && tempo < 95)
        node->line.setFillColor(sf::Color::Yellow);
    else if (tempo >= 95)
        node->line.setFillColor(orange);
    else
        node->line.setFillColor(sf::Color::Green);
    node->next = nullptr;
    if (this->GraphLinkedListLenRam == 0)
        this->_my_Ram = node;
    else {
        temp = this->_my_Ram;
        node->next = temp;
        this->_my_Ram = node;
    }
    this->GraphLinkedListLenRam += 1;
}

void Gui::add_element_swap(SysInfo system)
{
    GraphLinkedList *node;
    GraphLinkedList *temp;
    sf::Color orange;

    orange.a = 255;
    orange.r = 255;
    orange.b = 0;
    orange.g = 127;
    float tempo = 0;
    node = new GraphLinkedList;
    system.refresh_data();
    tempo = std::atof(system._ram.SwapUsagePercent().c_str());
    node->line.setSize(sf::Vector2f{2, (float)(1.43 * (std::atof(system._ram.SwapUsagePercent().c_str())))});
    if (tempo == 100)
        node->line.setFillColor(sf::Color::Red);
    else if (tempo >= 50 && tempo < 95)
        node->line.setFillColor(sf::Color::Yellow);
    else if (tempo >= 95)
        node->line.setFillColor(orange);
    else
        node->line.setFillColor(sf::Color::Green);
    node->next = nullptr;
    if (this->GraphLinkedListLenSwap == 0)
        this->_my_Swap = node;
    else {
        temp = this->_my_Swap;
        node->next = temp;
        this->_my_Swap = node;
    }
    this->GraphLinkedListLenSwap += 1;
}

void Gui::add_element(SysInfo system)
{
    //
    GraphLinkedList *node;
    GraphLinkedList *temp;
    sf::Color orange;

    orange.a = 255;
    orange.r = 255;
    orange.b = 0;
    orange.g = 127;
    float tempo = 0;
    for (size_t i = 0; i < (system._cpu._ThreadNb + 1); i += 1) {
        node = new GraphLinkedList;
        tempo = std::stof((std::string)(system._cpu._cpuinfo.cpu_info[i].substr(0, (system._cpu._cpuinfo.cpu_info[i].length() - 1))));
        node->line.setSize(sf::Vector2f{2, ((this->_height_mini_box / 100) * tempo)});
        if (tempo >= 50 && tempo < 99)
            node->line.setFillColor(sf::Color::Yellow);
        else if (tempo >= 99)
            node->line.setFillColor(orange);
        else
            node->line.setFillColor(sf::Color::Green);
        node->next = nullptr;
        if (this->GraphLinkedListLen == 0)
            this->_GraphLinkedList[i] = node;
        else {
            temp = this->_GraphLinkedList[i];
            node->next = temp;
            this->_GraphLinkedList[i] = node;
        }
    }
    this->GraphLinkedListLen += 1;
}

void Gui::display_Graph(SysInfo system)
{
    GraphLinkedList *temp;
    sf::Vector2f tempo;
    sf::Vector2f tempoo;
    add_element(system);
    for (size_t i = 0; i < system._cpu._ThreadNb; i += 1) {
        temp = this->_GraphLinkedList[(i + 1)];
        temp->line.setPosition(sf::Vector2f{this->_width_mini_box + 10, (((this->_height_mini_box) * (i + 1) + (12 * (i + 1))) - 2)});
        temp->line.setScale(sf::Vector2f{1, -1});
        tempo = temp->line.getPosition();
        this->_window.draw(temp->line);
        temp = temp->next;
        for (; temp != nullptr; temp = temp->next) {
            tempo.x -= 1;
            temp->line.setScale(sf::Vector2f{1, -1});
            temp->line.setPosition(tempo);
            tempo = temp->line.getPosition();
            this->_window.draw(temp->line);
        }
    }
    temp = this->_GraphLinkedList[0];
    temp->line.setPosition(sf::Vector2f{(float)this->getscreenWidth(), (float)this->getscreenHeight()});
    temp->line.setPosition((sf::Vector2f){(temp->line.getPosition().x / 2) + 60, (temp->line.getPosition().y / 2) - 5});
    temp->line.setScale(sf::Vector2f{2.025, -4});
    tempo = temp->line.getPosition();
    this->_window.draw(temp->line);
    temp = temp->next;
    int ppe = 0;
    for (; temp != nullptr; temp = temp->next) {
        ppe += 1;
        tempo.x -= 4.05;
        temp->line.setScale(sf::Vector2f{2.025, -4});
        temp->line.setPosition(tempo);
        tempo = temp->line.getPosition();
        this->_window.draw(temp->line);
    }
    if (this->GraphLinkedListLen >= (this->_width_mini_box)) {
        for (size_t i = 0; i < (system._cpu._ThreadNb + 1); i += 1)
            del_element(i);
        this->GraphLinkedListLen -= 1;
    }
}

void Gui::display_Graph_Ram(SysInfo system)
{
    GraphLinkedList *temp;
    sf::Vector2f tempo;
    sf::Vector2f tempoo;
    add_element_ram(system);


    temp = this->_my_Ram;
    temp->line.setPosition(sf::Vector2f{920, 500});
    temp->line.setScale(sf::Vector2f{1, -1});
    tempo = temp->line.getPosition();
    this->_window.draw(temp->line);
    temp = temp->next;
    for (; temp != nullptr; temp = temp->next) {
        tempo.x -= 1;
        temp->line.setScale(sf::Vector2f{1, -1});
        temp->line.setPosition(tempo);
        tempo = temp->line.getPosition();
        this->_window.draw(temp->line);
    }
    if (this->GraphLinkedListLenRam >= (220)) {
        del_element_ram();
        this->GraphLinkedListLenRam -= 1;
    }
}

void Gui::display_Graph_Swap(SysInfo system)
{
    GraphLinkedList *temp;
    sf::Vector2f tempo;
    sf::Vector2f tempoo;
    add_element_swap(system);


    temp = this->_my_Swap;
    temp->line.setPosition(sf::Vector2f{1177, 500});
    temp->line.setScale(sf::Vector2f{1, -1});
    tempo = temp->line.getPosition();
    this->_window.draw(temp->line);
    temp = temp->next;
    for (; temp != nullptr; temp = temp->next) {
        tempo.x -= 1;
        temp->line.setScale(sf::Vector2f{1, -1});
        temp->line.setPosition(tempo);
        tempo = temp->line.getPosition();
        this->_window.draw(temp->line);
    }
    if (this->GraphLinkedListLenSwap >= (220)) {
        del_element_swap();
        this->GraphLinkedListLenSwap -= 1;
    }
}

void Gui::print_network(SysInfo system)
{
    sf::Font myFont;
    myFont.loadFromFile("assets/Agency_FB.ttf");
    sf::Text pourcentage("empty", myFont, 28);
    pourcentage.setOutlineThickness(1);
    pourcentage.setOrigin(sf::Vector2f{10, 10});
    pourcentage.setFillColor(sf::Color::Cyan);

    pourcentage.setCharacterSize(25);
    print_text(this->_window, pourcentage, "Network:", (sf::Vector2f){170, 525});
    print_text(this->_window, pourcentage, "Receive packets : " + (system._network._receive_packet), (sf::Vector2f){170, 575});
    print_text(this->_window, pourcentage, "Receive bytes : " + (system._network._receive_bytes), (sf::Vector2f){170, 625});
    print_text(this->_window, pourcentage, "Transmit packets : " + (system._network._transmit_packet), (sf::Vector2f){370, 575});
    print_text(this->_window, pourcentage, "Transmit bytes : " + (system._network._transmit_bytes), (sf::Vector2f){370, 625});
}

void Gui::print_info(SysInfo system)
{
    sf::Font myFont;
    myFont.loadFromFile("assets/Agency_FB.ttf");
    sf::Text pourcentage("empty", myFont, 28);
    pourcentage.setOutlineThickness(1);
    pourcentage.setOrigin(sf::Vector2f{10, 10});
    pourcentage.setFillColor(sf::Color::Cyan);
    if (module_info) {
        print_text(this->_window, pourcentage, "Username: " + system._username, (sf::Vector2f){700, 50});
        print_text(this->_window, pourcentage, "Hostname: " + system._hostname, (sf::Vector2f){700, 100});
        print_text(this->_window, pourcentage, "Operating System name: " + (std::string)system._os.sysname, (sf::Vector2f){700, 150});
        print_text(this->_window, pourcentage, "Kernel version: " + (std::string)system._os.version, (sf::Vector2f){700, 200});
        print_text(this->_window, pourcentage, "Date and time: " + (std::string)get_time(), (sf::Vector2f){700, 250});
    }
    pourcentage.setCharacterSize(25);
    if (module_cpu_info) {
        print_text(this->_window, pourcentage, "Cpu Model: " + (std::string)system._cpu._CpuName, (sf::Vector2f){170, 375});
        print_text(this->_window, pourcentage, "Number of physic core: " + std::to_string(system._cpu._CoreNb), (sf::Vector2f){170, 425});
        print_text(this->_window, pourcentage, "Number of Thread: " + std::to_string(system._cpu._ThreadNb), (sf::Vector2f){170, 475});
    }
    if (module_ram)
        print_text(this->_window, pourcentage, "RAM USAGE:", (sf::Vector2f){765, 520});
    if (module_swap)
        print_text(this->_window, pourcentage, "SWAP USAGE:", (sf::Vector2f){1015, 520});
    system.refresh_data();
    pourcentage.setCharacterSize(40);
    if (module_ram)
        print_text(this->_window, pourcentage, system._ram.RamUsagePercent().substr(0, (3 + system._ram.RamUsagePercent().find_first_of(".", 0))) + " %", (sf::Vector2f){765, 415});
    if (module_swap)
        print_text(this->_window, pourcentage, system._ram.SwapUsagePercent().substr(0, (3 + system._ram.SwapUsagePercent().find_first_of(".", 0))) + " %", (sf::Vector2f){1020, 415});

}

void Gui::check_bool()
{
    if (this->_event.key.code
     == (sf::Keyboard::C)) {
        this->module_cpu_info = (module_cpu_info) ? (false) : (true);
        this->_event.key.code = sf::Keyboard::A;
    }
    if (this->_event.key.code == (sf::Keyboard::R)) {
        this->module_ram = (module_ram) ? (false) : (true);
        this->_event.key.code = sf::Keyboard::A;
    }
    if (this->_event.key.code == (sf::Keyboard::N)) {
        this->module_net = (module_net) ? (false) : (true);
        this->_event.key.code = sf::Keyboard::A;
    }
    if (this->_event.key.code == (sf::Keyboard::I)) {
        this->module_info = (module_info) ? (false) : (true);
        this->_event.key.code = sf::Keyboard::A;
    }
    if (this->_event.key.code == (sf::Keyboard::S)) {
        this->module_swap = (module_swap) ? (false) : (true);
        this->_event.key.code = sf::Keyboard::A;
    }
    if (this->_event.key.code == (sf::Keyboard::G)) {
        this->module_cpu_graph = (module_cpu_graph) ? (false) : (true);
        this->_event.key.code = sf::Keyboard::A;
    }
    if (this->_event.key.code == (sf::Keyboard::P)) {
        this->module_cpu_pourcentage = (module_cpu_pourcentage) ? (false) : (true);
        this->_event.key.code = sf::Keyboard::A;
    }
}

int Gui::Graphical(SysInfo &system)
{
    system.refresh_cpu_info();
    this->_window.clear();
    display_block(system);
    display_value(system);
    this->_window.display();
    while (this->_window.isOpen()) {
        my_time = clk.getElapsedTime();
        if ((my_time.asSeconds() - my_time_d.asSeconds()) >= 0.25) {
            my_time_d = my_time;
            system.refresh_data();
            this->_window.clear();
            //this->_window.draw(this->wallpaper);
            if (this->module_cpu_graph) {
                display_Graph_Ram(system);
                display_Graph_Swap(system);
                display_Graph(system);
            }
            if (this->module_cpu_pourcentage)
                display_value(system);
            if (this->module_net)
                print_network(system);
            display_block(system);
            print_info(system);
            this->_window.display();
        }
        check_bool();
        while (this->_window.pollEvent(this->_event))
            if (this->_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                this->_window.close();
    }
    return 0;
}
