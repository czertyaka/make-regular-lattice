#include "data.hpp"
#include "log.hpp"
#include "csv.h"

#include <utility>
#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>

#define AREA_LENGTH 62000 // meters
#define AREA_HALF_LENGTH AREA_LENGTH/2
#define STEP_LENGTH 1000 // meters
#define GRID_SIZE AREA_LENGTH/STEP_LENGTH+1
#define MBA_GRID_SIZE 10

void check_if_file_exists(const std::filesystem::path& inputFile);

const t_doses& Data::Doses() const
{
    return doses;
}

const t_coordinates& Data::Coordinates() const
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
        check_if_file_exists(source);

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
    try
    {
        doses.resize(coordinates.size(), 0);

        using namespace mba;

        point<2> lowerCorner = {-AREA_HALF_LENGTH, -AREA_HALF_LENGTH};
        point<2> higherCorner = {AREA_HALF_LENGTH, AREA_HALF_LENGTH};

        mba::index<2> grid = {MBA_GRID_SIZE, MBA_GRID_SIZE};

        t_coordinates irregularCoordinates(irregularData.Coordinates());
        t_doses irregularDoses(irregularData.Doses());

        MBA<2> interp(lowerCorner, higherCorner, grid, irregularCoordinates, irregularDoses);

        for (size_t i = 0; i < coordinates.size(); ++i)
        {
            try
            {
                doses.at(i) = interp(coordinates.at(i));
            }
            catch(const std::out_of_range& ex)
            {
                doses.at(i) = i > 0 ? doses.at(i-1) : 0;
                LOG_WARNING("error while interpolating dose for point " << coordinates.at(i)[0] << " "
                    << coordinates.at(i)[1] << ", assigning previuos value " << doses.at(i));
            }
        }

        return true;
    }
    catch (...)
    {
        LOG_ERROR("unknown error while making regular lattice");
    }

    return false;
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
    coordinates.reserve(GRID_SIZE * GRID_SIZE);

    for (int x = -AREA_HALF_LENGTH; x <= AREA_HALF_LENGTH; x += STEP_LENGTH)
    {
        for (int y = AREA_HALF_LENGTH; y >= -AREA_HALF_LENGTH; y -= STEP_LENGTH)
        {
            coordinates.push_back({static_cast<double>(x), static_cast<double>(y)});
        }
    }
}

void check_if_file_exists(const std::filesystem::path& inputFile)
{
    if (!std::filesystem::exists(inputFile))
    {
        throw std::runtime_error(std::string("file \"") + inputFile.string() + "\" doesn't exist");
    }
}