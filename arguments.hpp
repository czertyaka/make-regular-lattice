#pragma once

#include <filesystem>
#include <vector>

class Arguments
{
public:
    bool ParseArguments(int argc, char* argv[]);
    const std::filesystem::path& GetInputFile();
    const std::filesystem::path& GetOutputFile();
    bool IsHeader();
private:
    void CheckArgCount(int argc);
    void FillRawArguments(char* argv[]);
    void CheckInputFile();
    void CheckAndInitHeaderArgumnet();
    struct
    {
        std::string inputFile;
        std::string outputFile;
        std::string header;
    } rawArguments;
    std::filesystem::path inputFile;
    std::filesystem::path outputFile;
    bool header;
};