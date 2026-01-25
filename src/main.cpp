#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <algorithm>


namespace kv
{
    constexpr std::size_t MAX_KEY_LEN   = 256;
    constexpr std::size_t MAX_VALUE_LEN = 4096;

    inline bool has_whitespace(const std::string& s) {
        for (unsigned const char c : s) {
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v')
                return true;
        }
        return false;
    }
}

// Turns any string into uppercase
static std::string to_upper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),[](unsigned char c){ return std::toupper(c); });
    return s;
}


std::string execute(

    std::unordered_map<std::string, std::string>& map,
    const std::string& line)
{
    std::string command, key, value;

    // Check if line is empty
    if (line.empty()) return "ERR_EMPTY";

    std::stringstream ss(line);
    ss >> command;
    command = to_upper(command);

    if (command == "EXIT")
    {
        return "EXIT";
    }

    ss >> key;
    std::getline(ss >> std::ws, value);

    if (command == "PUT")
    {
        if (key.empty() || value.empty())
            return "ERR_USAGE PUT <key> <value>";

        map[key] = value;
        return "OK";

    } else if (command == "GET")
    {
        if (key.empty())
            return "ERR_USAGE GET <key>";

        auto it = map.find(key);
        if (it == map.end())
            return "NOT_FOUND";

        return it->second;

    } else if  (command == "DEL")
    {

        if (key.empty())
            return "ERR_USAGE DEL <key>";

        return map.erase(key) ? "OK" : "NOT_FOUND";

    } else if (command == "LIST")
    {
        std::string out;
        for (auto& [k, v] : map)
            out += k + " => " + v + "\n";

        return out.empty() ? "(empty)" : out;
    } else if  (command == "EXIT")
    {
        return "EXIT";
    }

    return "ERR_UNKNOWN_CMD";




}




int main ()
{
    std::unordered_map<std::string, std::string> store;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::string result = execute(store, line);

        if (result == "EXIT") break;

        std::cout << result << std::endl;
    }
}

