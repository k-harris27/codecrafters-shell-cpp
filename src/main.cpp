#include <iostream>
#include <string>
#include <sstream>
#include <vector>

const std::vector<std::string> BUILTINS {"exit", "echo", "type"};

void print_command_not_found(std::string& command) {
  std::cout << command << ": command not found" << std::endl;
}

int main() {
  while (true) {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);  // Read a line of input (up to \n)
    std::istringstream input_stream(input);

    std::string command;
    std::getline(input_stream, command, ' ');  // Extract the command (up to first space)

    if (command == "exit") {
      int exit_code = 0;
      if (std::getline(input_stream, command, ' ')) {
        exit_code = std::stoi(command);
      }
      return exit_code;
    }
    else if (command == "echo") {
      std::cout << input_stream.rdbuf() << std::endl;  // Print the remainder of the input string.
    }
    else if (command == "type") {
      std::string args;
      std::getline(input_stream, args);
      if (std::find(BUILTINS.begin(), BUILTINS.end(), args) != BUILTINS.end()) {
        std::cout << args << " is a shell builtin" << std::endl;
      }
      else {
        print_command_not_found(args);
      }
    }
    else {
      print_command_not_found(command);
    }
  }
}