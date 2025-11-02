#include <string>
#include <vector>
#include <iostream>

#include "builtins.hpp"

BuiltinResult BuiltinEcho(std::vector<std::string> &tokens)
{
  BuiltinResult result;
  // Skip the first token - that's the "echo" command.
  for (int i = 1; i < tokens.size(); i++)
  {
    std::cout << tokens[i] << " ";
  }
  std::cout << std::endl;
  return result;
}