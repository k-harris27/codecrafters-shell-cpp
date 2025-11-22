#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <unistd.h>

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

    auto target_str = target.string();
    if (target_str[0] == '~')
    {
      std::filesystem::path home_path = std::getenv("HOME");
      if (target_str.length() > 1)
      {
        target = home_path / std::string_view(target.c_str()).substr(2);
      }
      else
      {
        target = home_path;
      }
    }

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