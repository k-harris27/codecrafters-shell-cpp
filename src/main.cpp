#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "parser.hpp"
#include "builtins/builtins.hpp"

int main()
{
  while (true)
  {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input); // Read a line of input (up to \n)

    auto tokens = tokenise(input);

    // If the command is in kBuiltinMap, run the associated function.
    if (auto kvp = kBuiltinMap.find(tokens[0]); kvp != kBuiltinMap.end())
    {
      auto &builtin = kvp->second;
      BuiltinResult result = builtin(tokens);
      if (result.exit_shell)
      {
        return result.exit_code;
      }
      continue;
    }
    std::cout << input << ": command not found" << std::endl;
  }
}