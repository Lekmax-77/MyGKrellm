/*
** EPITECH PROJECT, 2022
** piscine_CPP
** File description:
** utils
*/

#include <string>

std::string clean_line(const std::string& line) {
    const char* whitespace = " \t\v\r\n";
    std::size_t begin = line.find_first_not_of(whitespace);
    std::size_t end = line.find_last_not_of(whitespace);

    if (begin == end)
        return (std::string());
    else
        return (line.substr(begin, end - begin + 1));
}