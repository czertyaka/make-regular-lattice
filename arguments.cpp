#include <iostream>
#include <utility>

#include "arguments.hpp"

#define EXPECTED_ARG_COUNT 3

bool Arguments::ParseArguments(int argc, char* argv[])
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
        std::cerr << "ERROR: " << err.what() << std::endl
            << "usage: mrl irregular_lattice_file regular_lattice_file {header|no_header}" << std::endl;
        return false;
    }

    return true;
}

const std::filesystem::path& Arguments::GetInputFile()
{
    return inputFile;
}

const std::filesystem::path& Arguments::GetOutputFile()
{
    return outputFile;
}

bool Arguments::IsHeader()
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