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

  bool in_single_quotes = false;
  for (char &c : input)
  {
    // Single quote behaviour
    if (in_single_quotes)
    {
      if (c == '\'')
      {
        in_single_quotes = false;
        continue;
      }
      word += c;
      continue;
    }

    // Default mode behaviour

    if (c == '\'')
    {
      in_single_quotes = true;
      continue;
    }
    if (c == ' ')
    {
      // Word ended - submit as newest token.
      if (word.length() > 0)
      {
        tokens.push_back(word);
        word = "";
      }
      // Make sure we also skip consecutive white spaces.
      continue;
    }
    word += c;
  }
  tokens.push_back(word);
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