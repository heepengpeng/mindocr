
#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H
#include <string>
#include <map>
class CommandParser {
public:
    CommandParser();
    ~CommandParser();
    void AddOption(const std::string &option, const std::string &defaults="", const std::string &message ="");
    void ParseArgs(int argc, const char **argv);
    const std::string &GetStringOption(const std::string &option);
    const int GetIntOption(const std::string &option);
    const uint32_t GetUint32Option(const std::string &option);
    const float GetFloatOption(const std::string &option);
    const double GetDoubleOption(const std::string &option);
    const bool GetBoolOption(const std::string &option);

private:
    std::map<std::string, std::pair<std::string, std::string>> m_commands;
    std::string ShowUsage() const;
    bool IsInteger(const std::string &input) const;
    bool IsDecimal(const std::string &input) const;

};

#endif
