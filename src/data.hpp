#include "mba.hpp"
#include "arguments.hpp"

#include <vector>

typedef struct _data
{
	std::vector<mba::point<2>> coordinates;
	std::vector<double> doses;
} t_data;

class DataRegularMaker
{
public:
	DataRegularMaker(const Arguments& args);
	bool ReadIrregularData();
	bool WriteRegularData();
private:
	void MakeRegularCoordinates();
	t_data irregularData;
	t_data regularData;
	const Arguments& args;
};