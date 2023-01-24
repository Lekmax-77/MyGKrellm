/*
** EPITECH PROJECT, 2022
** rush03
** File description:
** Gui
*/

#ifndef GUI_HPP_
    #define GUI_HPP_
    #include <string>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Audio.hpp>
    #include <SFML/Config.hpp>
    #include <SFML/GpuPreference.hpp>
    #include <SFML/OpenGL.hpp>
    #include <stdio.h>
    #include <stdlib.h>
    #include "../Monitor/IMonitorModule.hpp"

class IMonitorDisplay {
    public:
        virtual ~IMonitorDisplay() = default;
};


class GraphLinkedList
{
    public:
        sf::RectangleShape line;
        GraphLinkedList *next;
};

class Gui : public IMonitorDisplay
{
    public:
        Gui(const SysInfo &system);
        ~Gui();
        int getscreenWidth() const;
        int getscreenHeight() const;
        void del_element_swap();
        void del_element_ram();
        void del_element(int pos);
        void add_element(SysInfo system);
        void add_element_swap(SysInfo system);
        void add_element_ram(SysInfo system);
        void display_value(SysInfo system);
        void display_Graph_Ram(SysInfo system);
        void display_Graph_Swap(SysInfo system);
        void display_block(SysInfo system);
        void print_info(SysInfo system);
        void display_Graph(SysInfo system);
        int Graphical(SysInfo &system);
        std::string getscreenWindowTitle() const;
        void check_bool();
        void print_network(SysInfo system);
        void print_text(sf::RenderWindow &window, sf::Text contener, std::string text, sf::Vector2f pos);
        float _width_mini_box;
        float _height_mini_box;
        sf::Event _event;
        sf::RenderWindow _window;
        size_t GraphLinkedListLend;
        size_t GraphLinkedListLenSwap;
        size_t GraphLinkedListLenRam;
        size_t GraphLinkedListLen;
        GraphLinkedList *_GraphLinkedList[32];
        GraphLinkedList *_my_Ram;
        GraphLinkedList *_my_Swap;
        sf::Clock clk;
        sf::Time my_time;
        sf::Sprite wallpaper;
        sf::Time my_time_d;
        sf::Texture back;
        bool module_cpu_info = true;//         C
        bool module_ram = true;//              R >>>
        bool module_net = true;//              N
        bool module_info = true;//             I
        bool module_swap = true;//             S
        bool module_cpu_graph = true;//        G >>>
        bool module_cpu_pourcentage = true;//  P >>>
    protected:
    private:
        int _screen_height;
        std::string _window_title;
        int _screen_width;
};

int Graphical(SysInfo &system);
void display_block(Gui &Data, SysInfo system);

#endif /* !GUI_HPP_ */
