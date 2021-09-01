#include "log.hpp"
#include "arguments.hpp"
#include "mba.hpp"
#include "maker.hpp"

#include <array>

int main(int argc, char* argv[])
{
    Arguments args;
    if (!args.ParseArguments(argc, argv))
    {
        LOG_INFO("usage is as follows\n\tmrl irregular_lattice_file regular_lattice_file {header|no_header}");
        return -1;
    }

    DataRegularMaker maker(args);
    maker.ReadIrregularData();
    maker.MakeRegularData();
    maker.WriteRegularData();

    return 0;
}