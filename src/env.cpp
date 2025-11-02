#include "env.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

#ifdef _WIN32
const char kEnvPathDelim = ';';
#else
const char kEnvPathDelim = ':';
#endif

std::vector<std::string> GetPath()
{
  std::string path = std::getenv("PATH");

  std::vector<std::string> result;
  std::stringstream ss(path);
  std::string word;

  while (std::getline(ss, word, kEnvPathDelim))
  {
    result.push_back(word);
  }
  return result;
}

std::string FindInPath(const std::string &file)
{
  auto paths = GetPath();
  for (std::string &path : paths)
  {
    std::string test = path + '/' + file;
    std::ifstream f(test.c_str());
    if (f.good())
    {
      return test;
    }
  }
  return "";
}