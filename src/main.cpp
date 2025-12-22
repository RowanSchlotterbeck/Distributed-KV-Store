#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>

// Inserts a key, value pair into the map
void put(std::unordered_map<std::string, std::string>& map, const std::string& key,  const std::string& value)
{
    map[key] = value;
}

// Retrieves a value given its key
void get(const std::unordered_map<std::string, std::string>& map, std::string& key)
{
    if (map.find(key) != map.end())
    {
        std::cout << key << " => " << map.at(key) << "\n";
    }
    else
    {
        std::cout << key << " not found in map\n";
    }
}

// Deletes a key
void del(std::unordered_map<std::string, std::string>& map, std::string& key)
{
    map.erase(key);
}

int main ()
{

    // Init Data Structures
    std::unordered_map<std::string, std::string> umap;
    std::string line, command, argument;

    // While run until user types "EXIT"
    while (true){

        std::vector<std::string> args;

        std::cout<<"Enter your command (type EXIT to quit): ";
        std::getline(std::cin,line);
        std::stringstream ss(line);

        ss >> command;

        if (command == "EXIT")
        {
            break;
        }

        while (ss >> argument)
        {
            args.push_back(argument);
        }

        if (args.size() == 0 || args.size() > 2)
        {
            std::cout<< "Invalid amount of arguments" << std::endl;
            return 1;
        }

        if (command == "PUT")
        {
            if (args.size() != 2)
            {
                std::cout<< "Invalid arguments, correct use: PUT <key> <value>" << std::endl;
            }
            put(umap, args[0], args[1]);

            // Prints Map
            std::cout << std::endl;
            for (const auto& [k, v] : umap) {
                std::cout << k << " => " << v << "\n";
            }
            std::cout << std::endl;
        }

        if (command == "GET")
        {
            if (args.size() != 1)
            {
                std::cout<< "Invalid arguments, correct use: GET <key>" << std::endl;
            }
            get(umap, argument);

        }

        if (command == "DEL")
        {
            if (args.size() != 1)
            {
                std::cout<< "Invalid arguments, correct use: DEL <key>" << std::endl;
            }
            del(umap, argument);

            // Prints Map
            std::cout << std::endl;
            for (const auto& [k, v] : umap) {
                std::cout << k << " => " << v << "\n";
            }
            std::cout << std::endl;

        }
    }


}

