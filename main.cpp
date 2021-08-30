#include "log.hpp"
#include "arguments.hpp"
#include "fast-cpp-csv-parser/csv.h"

bool check_if_input_file_exists(const std::filesystem::path& inputFile);

int main(int argc, char* argv[])
{
    Arguments args;
    if (!args.ParseArguments(argc, argv))
    {
        INFO("usage is as follows\n\tmrl irregular_lattice_file regular_lattice_file {header|no_header}");
        return -1;
    }

    if (!check_if_input_file_exists(args.GetInputFile()))
    {
        return -1;
    }

    using namespace io;

    try
    {
        CSVReader<3, trim_chars<>, no_quote_escape<';'>> reader(args.GetInputFile().string());
        if (args.IsHeader())
        {
            reader.read_header(io::ignore_extra_column, "x", "y", "dose");
        }
        else
        {
            reader.set_header("x", "y", "dose");
        }
        int x, y;
        double dose;
        while(reader.read_row(x, y, dose))
        {

        }
    }
    catch (const error::base& err)
    {
        ERROR(err.what());
    }

    return 0;
}

bool check_if_input_file_exists(const std::filesystem::path& inputFile)
{
    if (!std::filesystem::exists(inputFile))
    {
        ERROR("ERROR: input file \"" << inputFile.string() << "\" doesn't exist");
        return false;
    }

    return true;
}