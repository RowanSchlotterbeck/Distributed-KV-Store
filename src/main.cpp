#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>


// Inserts a key, value pair into the map
void put(std::unordered_map<std::string, std::string>& map, const std::string& key,  const std::string& value)
{
    map[key] = value;
}

// Retrieves a value given its key
void get(const std::unordered_map<std::string, std::string>& map, const std::string& key)
{
    const auto it = map.find(key);

    if (it != map.end())
    {
        std::cout << it -> first << " => " << it -> second << "\n";
    }
    else
    {
        std::cout << key << " not found in map" << std::endl;
    }
}

// Deletes a key
void del(std::unordered_map<std::string, std::string>& map, const std::string& key)
{
    map.erase(key);
}

void print_map(const std::unordered_map<std::string, std::string>& map)
{
    std::cout << "\n";
    for (const auto& [k, v] : map) {
        std::cout << k << " => " << v << "\n";
    }
    std::cout << "\n";
}

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

        std::vector<std::string> args;
        std::string argument;

        while (ss >> argument)
        {
            args.push_back(argument);
        }

        if (command == "PUT")
        {
            if (args.size() != 2)
            {
                std::cout<< "Invalid arguments, correct use: PUT <key> <value>" << std::endl;
            } else
            {
                put(umap, args[0], args[1]);
            }

            print_map(umap);

        } else if (command == "GET")
        {
            if (args.size() != 1)
            {
                std::cout<< "Invalid arguments, correct use: GET <key>" << std::endl;
            } else
            {
                get(umap, args[0]);
            }


        } else if  (command == "DEL")
        {
            if (args.size() != 1)
            {
                std::cout<< "Invalid arguments, correct use: DEL <key>" << std::endl;
            }
            else
            {
                del(umap, args[0]);
            }

            // Prints Map
            print_map(umap);

        }
        else
        {
            std:: cout << "Invalid command: " << command <<  std::endl;
        }
    }
}

