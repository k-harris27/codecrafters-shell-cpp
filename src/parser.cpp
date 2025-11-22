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

  enum ParseMode
  {
    standard,
    single_quotes,
    double_quotes,
  };
  ParseMode mode = ParseMode::standard;

  for (char &c : input)
  {
    // Single quote behaviour
    if (mode == ParseMode::single_quotes)
    {
      if (c == '\'')
      {
        mode = ParseMode::standard;
        continue;
      }
      word += c;
      continue;
    }

    // Double quote behaviour
    if (mode == ParseMode::double_quotes)
    {
      if (c == '"')
      {
        mode = ParseMode::standard;
        continue;
      }
      word += c;
      continue;
    }

    // Default mode behaviour

    if (c == '\'')
    {
      mode = ParseMode::single_quotes;
      continue;
    }
    if (c == '"')
    {
      mode = ParseMode::double_quotes;
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