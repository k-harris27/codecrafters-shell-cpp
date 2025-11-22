#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "builtins.hpp"

BuiltinResult BuiltinCd(std::vector<std::string> &tokens)
{
  BuiltinResult result;
  int ntokens = tokens.size();
  if (ntokens > 2)
  {
    std::cout << "Too many arguments given to command \"cd\": " << ntokens - 1 << std::endl;
    result.exit_code = 1;
    return result;
  }
  std::filesystem::path target = "~";
  if (ntokens == 2)
  {
    target = tokens[1];
    if (!std::filesystem::exists(target))
    {
      std::cout << "cd: " << target.string() << ": No such file or directory" << std::endl;
      result.exit_code = 2;
      return result;
    }
  }
  std::filesystem::current_path(target); // Change directory
  return result;
}