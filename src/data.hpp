#include "mba.hpp"
#include "arguments.hpp"
#include "log.hpp"

#include <vector>

typedef mba::point<2> t_point;
typedef std::vector<t_point> t_coordinates;
typedef std::vector<double> t_doses;

class Data
{
public:
    const t_doses& Doses() const;
    const t_coordinates& Coordinates() const;
protected:
    t_coordinates coordinates;
    t_doses doses;
};

class IrregularData : public Data
{
public:
    IrregularData(const Arguments& args);
    IrregularData(const std::filesystem::path& source, const bool isHeader);
    bool Read();
private:
    const std::filesystem::path& source;
    const bool isHeader;
};

class RegularData : public Data
{
public:
    RegularData(const Arguments& args);
    RegularData(const std::filesystem::path& outputFile);
    bool Make(const Data& irregularData);
    bool Write();
private:
    void MakeCoordinates();
    const std::filesystem::path& outputFile;
};