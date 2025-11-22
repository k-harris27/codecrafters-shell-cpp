#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

struct BuiltinResult
{
  uint exit_code = 0;
  bool exit_shell = false;
};

BuiltinResult BuiltinEcho(std::vector<std::string> &tokens);
BuiltinResult BuiltinExit(std::vector<std::string> &tokens);
BuiltinResult BuiltinPwd(std::vector<std::string> &tokens);
BuiltinResult BuiltinType(std::vector<std::string> &tokens);

using BuiltinFunction = std::function<BuiltinResult(std::vector<std::string> &)>;

const std::unordered_map<std::string, BuiltinFunction> kBuiltinMap =
    {
        {"echo", BuiltinEcho},
        {"exit", BuiltinExit},
        {"pwd", BuiltinPwd},
        {"type", BuiltinType},
};