#include <iostream>
#include <string>

int main() {
  while (true) {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);  // Read a line of input (up to \n)
    std::cout << input << ": command not found" << std::endl;
  }
}
