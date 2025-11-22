#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "builtins.hpp"

BuiltinResult BuiltinPwd(std::vector<std::string> &tokens)
{
  BuiltinResult result;
  std::cout << std::filesystem::current_path().string() << std::endl;
  return result;
}