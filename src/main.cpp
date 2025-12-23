#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <algorithm>
#include <optional>

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

// Inserts a key, value pair into the map
// Doesn't throw exceptions, handles errors internally
std::optional<std::string> put(std::unordered_map<std::string, std::string>& map, const std::string& key,  const std::string& value) noexcept
{

    // Validate input
    if (key.empty()) return "ERR_EMPTY_KEY";
    if (key.size() > kv::MAX_KEY_LEN) return "ERR_KEY_TOO_LONG";
    if (kv::has_whitespace(key))      return "ERR_INVALID_KEY";
    if (value.size() > kv::MAX_VALUE_LEN) return "ERR_VALUE_TOO_LONG";

    // Guarantees one response, returns "OK" for valid operation
    try
    {
        map.insert_or_assign(key, value);
        return "OK";
    } catch (const std::bad_alloc&)
    {
        return "ERR_OOM";
    } catch (...)
    {
        return "ERR_INTERNAL";
    }

}

// Retrieves a value given its key
std::optional<std::string> get(const std::unordered_map<std::string, std::string>& map, const std::string& key)
{
    const auto it = map.find(key);

    if (it == map.end()) return std::nullopt;

    return it -> second;
}

// Deletes a key
std::string del(std::unordered_map<std::string, std::string>& map, const std::string& key)
{
    const auto it = map.find(key);

    if (it == map.end())
    {
        return "NOT_FOUND";
    }
    else
    {
        map.erase(it -> first);
        return "OK";
    }

}

// Prints the map
void print_map(const std::unordered_map<std::string, std::string>& map)
{
    std::cout << "\n";
    for (const auto& [k, v] : map) {
        std::cout << k << " => " << v << "\n";
    }
    std::cout << "\n";
}

// Turns any string into uppercase
static std::string to_upper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),[](unsigned char c){ return std::toupper(c); });
    return s;
}



int main ()
{

    // Init Data Structures
    std::unordered_map<std::string, std::string> umap;
    std::string line, command;

    // While run until user types "EXIT"
    while (true){


        std::cout<<"Enter your command (type EXIT to quit): ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        std::stringstream ss(line);
        ss >> command;
        command = to_upper(command);

        if (command == "EXIT")
        {
            break;
        }

        std::string key;
        std::string value;

        ss >> key;
        std::getline(ss >> std::ws, value);

        if (command == "PUT")
        {
            if (key.empty() || value.empty())
            {
                std::cout<< "Invalid arguments, correct use: PUT <key> <value>" << std::endl;
            } else
            {
                put(umap, key, value);
            }



        } else if (command == "GET")
        {
            if (key.empty())
            {
                std::cout<< "Invalid arguments, correct use: GET <key>" << std::endl;
            } else
            {
                const auto retVal = get(umap, key);
                if (retVal) std::cout << *retVal << std::endl;
                else std::cout << "NOT_FOUND" << std::endl;
            }

        } else if  (command == "DEL")
        {

            if (key.empty())
            {
                std::cout<< "Invalid arguments, correct use: DEL <key>" << std::endl;
            }
            else
            {
                std::string retVal;
                retVal = del(umap, key);
                std::cout << retVal << std::endl;
            }

        }
        else if (command == "LIST")
        {
            print_map(umap);
        }
        else
        {
            std:: cout << "Invalid command: " << command <<  std::endl;
        }
    }
}

