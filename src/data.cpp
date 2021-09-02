#include "data.hpp"
#include "log.hpp"
#include "csv.h"

#include <utility>
#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>

#define AREA_LENGTH 60000 // meters
#define AREA_HALF_LENGTH AREA_LENGTH/2
#define STEP_LENGTH 1000 // meters

void check_if_input_file_exists(const std::filesystem::path& inputFile);

const t_doses& Data::Doses()
{
    return doses;
}

const t_coordinates& Data::Coordinates()
{
    return coordinates;
}

IrregularData::IrregularData(const Arguments& args) :
    source(args.GetInputFile()),
    isHeader(args.IsHeader())
{}

IrregularData::IrregularData(const std::filesystem::path& source, const bool isHeader) :
    source(source),
    isHeader(isHeader)
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

        double x, y;
        double dose;
        LOG_DEBUG("reading input file " << source.string());
        while(reader.read_row(x, y, dose))
        {
            coordinates.push_back({x, y});
            doses.push_back(dose);
        }

        if (coordinates.size() == 0)
        {
            LOG_WARNING("empty input file " << source.string());
        }

        LOG_DEBUG(coordinates.size() << " values were successfully read");
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
        if (std::find(coordinates.cbegin(), coordinates.cend(), *node) == coordinates.cend())
        {
            LOG_DEBUG("adding corner node to input data x = " << node->at(0) << ", y = " << node->at(1));
            coordinates.push_back(*node);
            doses.push_back(0);
        }
    }
}

RegularData::RegularData(const Arguments& args) :
    outputFile(args.GetOutputFile())
{
    MakeCoordinates();
}

RegularData::RegularData(const std::filesystem::path& outputFile) :
    outputFile(outputFile)
{
    MakeCoordinates();
}

bool RegularData::Make(const Data& irregularData)
{
    doses.resize(coordinates.size(), 0);
    return true;
}

bool RegularData::Write()
{
    try
    {
        std::ofstream of(outputFile.string());
        if (!of.good())
        {
            throw std::runtime_error("error writin to output file " + outputFile.string());
        }
        of << "x;y;dose";
        for (size_t i = 0; i < coordinates.size(); ++i)
        {
            of << std::endl << coordinates.at(i).at(0) << ';' << coordinates.at(i).at(1)
                << ';' << doses.at(i);
        }
        of.close();
        LOG_INFO("regular lattice written to " << outputFile.string());
        return true;
    }
    catch (const std::runtime_error& err)
    {
        LOG_ERROR(err.what());
    }
    catch (const std::exception& err)
    {
        LOG_ERROR(err.what());
    }
    catch (...)
    {
        LOG_ERROR("unknown error while writing to " << outputFile.string());
    }
    return false;
}

void RegularData::MakeCoordinates()
{
    constexpr size_t regularNodesNumber = AREA_LENGTH / STEP_LENGTH + 1;
    coordinates.reserve(regularNodesNumber * regularNodesNumber);

    for (int y = AREA_HALF_LENGTH; y >= -AREA_HALF_LENGTH; y -= STEP_LENGTH)
    {
        for (int x = -AREA_HALF_LENGTH; x <= AREA_HALF_LENGTH; x += STEP_LENGTH)
        {
            coordinates.push_back({static_cast<double>(x), static_cast<double>(y)});
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