#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "builtins.hpp"
#include "../env.hpp"

BuiltinResult BuiltinType(std::vector<std::string> &tokens)
{
  BuiltinResult result;
  if (tokens.size() < 2)
  {
    std::cout << "No command specified" << std::endl;
    result.exit_code = 1;
    return result;
  }
  else if (tokens.size() > 2)
  {
    std::cout << "Too many arguments, expected 1" << std::endl;
    result.exit_code = 2;
    return result;
  }

  // Builtin
  const std::string &command = tokens[1];
  if (kBuiltinMap.find(command) != kBuiltinMap.end())
  {
    std::cout << command << " is a shell builtin" << std::endl;
    return result;
  }

  // External executable (PATH)
  if (auto path = FindInPath(command); !path.empty())
  {
    std::cout << command << " is " << path << std::endl;
    return result;
  }

  // Fallback
  std::cout << command << ": not found" << std::endl;
  return result;
}