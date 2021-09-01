#include "data.hpp"
#include "log.hpp"
#include "csv.h"

#include <utility>

#define AREA_LENGTH 60000 // meters
#define STEP_LENGTH 1000 // meters

void check_if_input_file_exists(const std::filesystem::path& inputFile);

DataRegularMaker::DataRegularMaker(const Arguments& args) :
    args(args)
{
    MakeRegularCoordinates();
}

bool DataRegularMaker::ReadIrregularData()
{
    try
    {
        check_if_input_file_exists(args.GetInputFile());

        using namespace io;
        CSVReader<3, trim_chars<>, no_quote_escape<';'>> reader(args.GetInputFile().string());

        if (args.IsHeader())
        {
            reader.read_header(io::ignore_extra_column, "x", "y", "dose");
        }
        else
        {
            reader.set_header("x", "y", "dose");
        }

        double x, y, dose;
        while(reader.read_row(x, y, dose))
        {
            irregularData.coordinates.push_back({x, y});
            irregularData.doses.push_back(dose);
            LOG_DEBUG("x = " << x << ", y = " << y << ", dose = " << dose);
        }

        return true;
    }
    catch (const io::error::base& err)
    {
        LOG_ERROR(err.what());
    }
    catch (const std::runtime_error& err)
    {
        LOG_ERROR(err.what());
    }

    return false;
}

bool DataRegularMaker::WriteRegularData()
{
    return false;
}

void DataRegularMaker::MakeRegularCoordinates()
{
    constexpr size_t regularNodesNumber = AREA_LENGTH / STEP_LENGTH + 1;
    regularData.coordinates.reserve(regularNodesNumber * regularNodesNumber);

    LOG_DEBUG("making regular coordinates");
    for (int x = -AREA_LENGTH/2; x <= AREA_LENGTH/2; x += STEP_LENGTH)
    {
        for (int y = AREA_LENGTH/2; y >= -AREA_LENGTH/2; y -= STEP_LENGTH)
        {
            regularData.coordinates.push_back({static_cast<double>(x), static_cast<double>(y)});
            LOG_DEBUG("x = " << x << ", y = " << y);
        }
    }
}

void check_if_input_file_exists(const std::filesystem::path& inputFile)
{
    if (!std::filesystem::exists(inputFile))
    {
        throw std::runtime_error(std::string("input file \"") + inputFile.string() + "\" doesn't exist");
    }
}