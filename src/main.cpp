#include <iostream>
#include <unordered_map>
#include <string>
#include "../include/parser.hpp"
#include "../include/kv_store.hpp"







int main ()
{
    std::unordered_map<std::string, std::string> store;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::string result;
        auto args = input_parser(line);
        if (args[0] == "Error")
        {
            result = "INPUT_ERROR";
        } else
        {
            result = execute(store, args);
        }


        if (result == "EXIT")
            break;

        std::cout << result << std::endl;
    }
}

