#include <stringdefs.h>
#include <sstream>

// Probably a better way of doing this, but that's not the goal of this program.
// https://stackoverflow.com/a/5167641
std::vector<String> splitString(String& str, char seperator)
{
    std::vector<String> items;
    String::size_type pos = 0, prev_pos = 0;

    while ((pos = str.find(seperator, pos)) != String::npos) {
        String substring = str.substr(prev_pos, pos - prev_pos);
        items.push_back(substring);
        prev_pos = ++pos;
    }

    items.push_back(str.substr(prev_pos, pos - prev_pos)); // Last word

    return items;
}

int const hexToInt(wchar_t& symbol)
{
    // TODO : Implement
    return 0;
}

char const intToHex(int& value)
{
    // TODO : Implement
    return '0';
}
