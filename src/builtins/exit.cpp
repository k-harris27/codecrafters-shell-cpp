#include <iostream>
#include <string>
#include <vector>

#include "builtins.hpp"

BuiltinResult BuiltinExit(std::vector<std::string> &tokens)
{
  int ntokens = tokens.size();
  BuiltinResult result = {0, false};
  if (ntokens > 2)
  {
    std::cout << "Too many arguments given to command \"exit\": " << ntokens - 1 << std::endl;
    result.exit_code = 1;
    return result;
  }
  else if (ntokens == 2)
  {
    try
    {
      result.exit_code = std::stoi(tokens[1]);
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "Exit code must be an integer." << std::endl;
      result.exit_code = 1;
      return result;
    }
  }
  result.exit_shell = true;
  return result;
}
