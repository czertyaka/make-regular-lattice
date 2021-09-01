#include "mba.hpp"
#include "arguments.hpp"

#include <vector>

typedef struct _data
{
	std::vector<mba::point<2>> coordinates;
	std::vector<double> doses;
} t_data;

class IrregularData
{
public:
    IrregularData(const Arguments& args);
    bool Read();
    void AddCornerNodes();
private:
    const std::filesystem::path& source;
    bool isHeader;
    t_data data;
};

class DataRegularMaker
{
public:
	DataRegularMaker(const Arguments& args);
	bool MakeRegularData();
	bool WriteRegularData();
private:
	void MakeRegularCoordinates();
	t_data irregularData;
	t_data regularData;
	const Arguments& args;
};