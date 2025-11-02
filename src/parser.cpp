#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

// Split input string into tokens separated by whitespace.
vector<string> tokenise(string &input)
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