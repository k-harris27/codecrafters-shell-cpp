#include <string>
#include <vector>

// Split input string into tokens separated by whitespace.
std::vector<std::string> Tokenise(std::string &input);

// Convert a c++ style vector of strings to a c-style array of char strings, including NULL termination.
// Based on https://stackoverflow.com/a/7048972
std::vector<char const *> StrVectorToChars(std::vector<std::string> input);