#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

vector<string> Tokenise(string &input)
{
  vector<string> tokens;
  std::stringstream ss(input);
  string word;

  while (std::getline(ss, word, ' '))
  {
    tokens.push_back(word);
  }

  return tokens;
}

char const *const StrToChar(const string &s)
{
  return s.c_str();
}

vector<char const *> StrVectorToChars(vector<string> input)
{
  vector<char const *> vc;
  std::transform(input.begin(), input.end(), std::back_inserter(vc), StrToChar);
  vc.push_back(NULL); // Make sure to include null terminator.
  return vc;
}