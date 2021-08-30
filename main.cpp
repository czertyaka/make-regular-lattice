#include <iostream>
#include <utility>
#include <filesystem>

static std::filesystem::path irregularLatticeFile;
static std::filesystem::path regularLatticeFile;
static bool header;

bool parse_arguments(const int argc, char* argv[]);
void do_parse_arguments(const int argc, char* argv[]);

int main(int argc, char* argv[])
{
    if (!parse_arguments(argc, argv))
    {
        return -1;
    }

    return 0;
}

bool parse_arguments(const int argc, char* argv[])
{
    try
    {
        do_parse_arguments(argc, argv);
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "ERROR: " << err.what() << std::endl
            << "usage: mrl irregular_lattice_file regular_lattice_file {header|no_header}" << std::endl;
        return false;
    }

    return true;
}

void do_parse_arguments(const int argc, char* argv[])
{
    if (argc != 4)
    {
        throw std::runtime_error("invalid arguments number");
    }

    irregularLatticeFile = std::filesystem::path(argv[1]);
    if (!std::filesystem::exists(irregularLatticeFile))
    {
        throw std::runtime_error("input file \"" + irregularLatticeFile.string() + std::string("\" doesn't exist"));
    }

    regularLatticeFile = std::filesystem::path(argv[2]);

    std::string headerArgument(argv[3]);
    if (headerArgument == "header")
    {
        header = true;
    }
    else if (headerArgument == "no_header")
    {
        header = false;
    }
    else
    {
        throw std::runtime_error("third argument should be \"header\" or \"no_header\"");
    }
}