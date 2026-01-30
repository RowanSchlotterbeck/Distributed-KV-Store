
#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>

// Parses the input command line into arguments, handling strictly quoted keys/values.
// Returns a vector of strings representing command and args, or {"Error"} if input is invalid.
std::vector<std::string> input_parser(const std::string& line);

#endif // PARSER_HPP

