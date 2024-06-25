#include "util.h"

std::string Util::centerString(const std::string &str, int width, bool center)
{
    int padLen = center ? (width - str.length()) / 2 : (CONSOLE_WIDTH - (str.length() + (width - str.length()))) / 2;
    if (padLen < 0)
    {
        padLen = 0;
    }
    std::string padding(padLen, ' ');
    return padding + str;
}

std::string Util::setPadding(std::string str, int width, char align)
{
    int length = str.length();
    if (length >= width)
        return str;
    int diff = width - length;
    int pad1 = diff / 2;
    int pad2 = diff - pad1;
    if (align == 'l')
        return str + std::string(diff, ' ');
    else if (align == 'r')
        return std::string(diff, ' ') + str;
    else
        return std::string(pad1, ' ') + str + std::string(pad2, ' ');
}