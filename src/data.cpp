#include "data.hpp"
#include "log.hpp"

#define AREA_LENGTH 60000 // meters
#define STEP_LENGTH 1000 // meters

DataRegularMaker::DataRegularMaker(const Arguments& args) :
	args(args)
{
	MakeRegularCoordinates();
}

bool DataRegularMaker::ReadIrregularData()
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