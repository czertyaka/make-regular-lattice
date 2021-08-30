#include "arguments.hpp"
#include <iostream>

bool check_if_input_file_exists(const std::filesystem::path& inputFile);

int main(int argc, char* argv[])
{
    Arguments args;
    if (!args.ParseArguments(argc, argv) || !check_if_input_file_exists(args.GetInputFile()))
    {
        return -1;
    }

    return 0;
}

bool check_if_input_file_exists(const std::filesystem::path& inputFile)
{
    if (!std::filesystem::exists(inputFile))
    {
        std::cerr << "ERROR: input file \"" << inputFile.string() << "\" doesn't exist" << std::endl;
        return false;
    }

    return true;
}