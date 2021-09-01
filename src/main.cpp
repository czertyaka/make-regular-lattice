#include "log.hpp"
#include "arguments.hpp"
#include "csv.h"
#include "mba.hpp"
#include "data.hpp"

#include <array>

bool check_if_input_file_exists(const std::filesystem::path& inputFile);

int main(int argc, char* argv[])
{
    Arguments args;
    if (!args.ParseArguments(argc, argv))
    {
        LOG_INFO("usage is as follows\n\tmrl irregular_lattice_file regular_lattice_file {header|no_header}");
        return -1;
    }

    if (!check_if_input_file_exists(args.GetInputFile()))
    {
        return -1;
    }

    DataRegularMaker maker(args);

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
        double x, y;
        double dose;
        std::vector<mba::point<2>> coordinates;
        std::vector<double> doses;
        while(reader.read_row(x, y, dose))
        {
            coordinates.push_back({x, y});
            doses.push_back(dose);
            LOG_DEBUG("x = " << x << ", y = " << y << ", dose = " << dose);
        }
    }
    catch (const error::base& err)
    {
        LOG_ERROR(err.what());
    }

    return 0;
}

bool check_if_input_file_exists(const std::filesystem::path& inputFile)
{
    if (!std::filesystem::exists(inputFile))
    {
        LOG_ERROR("input file \"" << inputFile.string() << "\" doesn't exist");
        return false;
    }

    return true;
}