#pragma once

#define CONSOLE_WIDTH 148

#include <iostream>
#include <string>

class Util
{
public:
    static std::string centerString(const std::string &str, int width = CONSOLE_WIDTH, bool center = true);
    static std::string setPadding(std::string str, int width, char align = 'c');
};