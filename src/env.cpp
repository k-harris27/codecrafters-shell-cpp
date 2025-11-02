#include "env.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>

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
#ifdef _WIN32
  // TODO: access will fail for windows
  // need: https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getbinarytypea
  throw std::exception("Not Implemented: env.cpp::FindInPath() cannot currently run on Windows.");
#endif

  auto paths = GetPath();
  for (std::string &path : paths)
  {
    std::string test = path + '/' + file;
    if (!access(test.c_str(), X_OK)) // POSIX: Check if file exists and is executable
    {
      return test;
    }
  }
  return "";
}