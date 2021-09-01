#include "log.hpp"
#include "arguments.hpp"
#include "data.hpp"

#include <array>

int main(int argc, char* argv[])
{
    Arguments args;
    if (!args.ParseArguments(argc, argv))
    {
        LOG_INFO("usage is as follows\n\tmrl irregular_lattice_file regular_lattice_file {header|no_header}");
        return -1;
    }

    IrregularData irregularData(args);
    irregularData.Read();
    irregularData.AddCornerNodes();

    RegularData regularData(args);
    regularData.Make(irregularData);
    regularData.Write();

    return 0;
}