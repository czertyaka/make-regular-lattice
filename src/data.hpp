#include "mba.hpp"
#include "arguments.hpp"

#include <vector>

typedef std::vector<mba::point<2>> t_coordinates;
typedef std::vector<double> t_doses;

class Data
{
protected:
	t_coordinates coordinates;
	std::vector<double> doses;
};

class IrregularData : public Data
{
public:
    IrregularData(const Arguments& args);
    bool Read();
    void AddCornerNodes();
private:
    const std::filesystem::path& source;
    bool isHeader;
};

class RegularData : public Data
{
public:
	RegularData(const Arguments& args);
	bool Make(const Data& irregularData);
	bool Write();
private:
	void MakeCoordinates();
	const std::filesystem::path& outputFile;
};

class DataRegularMaker
{
public:
	DataRegularMaker(const Arguments& args);
	bool MakeRegularData();
	bool WriteRegularData();
private:
	void MakeRegularCoordinates();
	Data irregularData;
	Data regularData;
	const Arguments& args;
};