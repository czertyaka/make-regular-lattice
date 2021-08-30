#include <iostream>
#include <utility>

#include "arguments.hpp"

#define EXPECTED_ARG_COUNT 3

bool Arguments::ParseArguments(int argc, char* argv[])
{
    try
    {
        CheckArgCount(argc);
        FillRawArguments(argv);
        inputFile = std::filesystem::path(rawArguments.inputFile);
        CheckInputFile();
        outputFile = std::filesystem::path(rawArguments.outputFile);
        CheckAndInitHeaderArgumnet();
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR: " << err.what() << std::endl
            << "usage: mrl irregular_lattice_file regular_lattice_file {header|no_header}" << std::endl;
        return false;
    }

    return true;
}

void Arguments::CheckArgCount(int argc)
{
    if ((argc-1) != EXPECTED_ARG_COUNT)
    {
        throw std::runtime_error("invalid arguments number");
    }
}

void Arguments::FillRawArguments(char* argv[])
{
    rawArguments.inputFile = std::string(argv[1]);
    rawArguments.outputFile = std::string(argv[2]);
    rawArguments.header = std::string(argv[3]);
}

void Arguments::CheckInputFile()
{
    if (!std::filesystem::exists(inputFile))
    {
        throw std::runtime_error("input file \"" + inputFile.string() + std::string("\" doesn't exist"));
    }
}

void Arguments::CheckAndInitHeaderArgumnet()
{
    if (rawArguments.header == "header")
    {
        header = true;
    }
    else if (rawArguments.header == "no_header")
    {
        header = false;
    }
    else
    {
        throw std::runtime_error("third argument should be \"header\" or \"no_header\"");
    }
}