#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include <unistd.h>
#include <sys/wait.h>

#include "parser.hpp"
#include "env.hpp"
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

    auto tokens = Tokenise(input);

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

    if (auto path = FindInPath(tokens[0]); path.length() > 0)
    {
      auto pid = fork();
      switch (pid)
      {
      case -1: // Failed to spawn new process
        throw std::runtime_error("An unexpected error occurred trying to start a new process.");
      case 0: // We are in child process
      {
        auto tokens_as_char = StrVectorToChars(tokens);
        int status_code = execvp(path.c_str(), const_cast<char *const *>(tokens_as_char.data()));
        if (status_code == -1)
        {
          std::cout << "External executable " << tokens[0] << " did not start correctly. Error " << errno << std::endl;
          exit(errno);
        }
        std::cout << "TEST: This line should never run." << std::endl;
        break;
      }
      default: // We are in the parent process (pid > 0)
        int child_status;
        waitpid(pid, &child_status, 0); // Wait for child process to finish
      }
      continue; // Return to the start of the REPL loop
    }

    std::cout << input << ": command not found" << std::endl;
  }
}