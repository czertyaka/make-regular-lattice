#include "maker.hpp"
#include "log.hpp"
#include "csv.h"

#include <utility>
#include <algorithm>

#define AREA_LENGTH 60000 // meters
#define AREA_HALF_LENGTH AREA_LENGTH/2
#define STEP_LENGTH 1000 // meters

void check_if_input_file_exists(const std::filesystem::path& inputFile);

IrregularData::IrregularData(const Arguments& args) :
    source(args.GetInputFile()),
    isHeader(args.IsHeader())
{}

bool IrregularData::Read()
{
    try
    {
        check_if_input_file_exists(source);

        using namespace io;
        CSVReader<3, trim_chars<>, no_quote_escape<';'>> reader(source.string());

        if (isHeader)
        {
            reader.read_header(io::ignore_extra_column, "x", "y", "dose");
        }
        else
        {
            reader.set_header("x", "y", "dose");
        }

        double x, y, dose;
        LOG_DEBUG("reading input file " << source.string());
        while(reader.read_row(x, y, dose))
        {
            data.coordinates.push_back({x, y});
            data.doses.push_back(dose);
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

void IrregularData::AddCornerNodes()
{
    t_coordinates cornerNodes = {
        {-AREA_HALF_LENGTH, AREA_HALF_LENGTH},
        {AREA_HALF_LENGTH, AREA_HALF_LENGTH},
        {-AREA_HALF_LENGTH, -AREA_HALF_LENGTH},
        {AREA_HALF_LENGTH, -AREA_HALF_LENGTH}
    };

    for (t_coordinates::const_iterator node = cornerNodes.cbegin(); node != cornerNodes.cend(); ++node)
    {
        if (std::find(data.coordinates.begin(), data.coordinates.end(), *node) != data.coordinates.end());
        {
            LOG_DEBUG("adding corner node to input data x = " << node->at(0) << ", y = " << node->at(1));
            data.coordinates.push_back(*node);
            data.doses.push_back(0);
        }
    }
}

DataRegularMaker::DataRegularMaker(const Arguments& args) :
    args(args)
{
    MakeRegularCoordinates();
}

bool DataRegularMaker::MakeRegularData()
{
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