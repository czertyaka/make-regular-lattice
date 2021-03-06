#include <utility>

#include "log.hpp"
#include "arguments.hpp"

#define EXPECTED_ARG_COUNT 3

bool Arguments::Parse(int argc, char* argv[])
{
    try
    {
        CheckArgCount(argc);
        inputFile = std::filesystem::path(argv[1]);
        outputFile = std::filesystem::path(argv[2]);
        CheckAndInitHeaderArgument(std::string(argv[3]));
    }
    catch (const std::runtime_error& err)
    {
        LOG_ERROR(err.what());
        return false;
    }

    return true;
}

const std::filesystem::path& Arguments::GetInputFile() const
{
    return inputFile;
}

const std::filesystem::path& Arguments::GetOutputFile() const
{
    return outputFile;
}

bool Arguments::IsHeader() const
{
    return header;
}

void Arguments::CheckArgCount(int argc)
{
    if ((argc-1) != EXPECTED_ARG_COUNT)
    {
        throw std::runtime_error("invalid arguments number");
    }
}

void Arguments::CheckAndInitHeaderArgument(const std::string& rawHeaderArgument)
{
    if (rawHeaderArgument == "header")
    {
        header = true;
    }
    else if (rawHeaderArgument == "no_header")
    {
        header = false;
    }
    else
    {
        throw std::runtime_error("third argument should be \"header\" or \"no_header\"");
    }
}