#pragma once

#include <filesystem>
#include <vector>

class Arguments
{
public:
    bool Parse(int argc, char* argv[]);
    const std::filesystem::path& GetInputFile() const;
    const std::filesystem::path& GetOutputFile() const;
    bool IsHeader() const;
private:
    void CheckArgCount(int argc);
    void CheckAndInitHeaderArgument(const std::string& rawHeaderArgument);
    std::filesystem::path inputFile;
    std::filesystem::path outputFile;
    bool header;
};