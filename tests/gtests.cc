#include <gtest/gtest.h>
#include <array>

#include "data.hpp"
#include "arguments.hpp"

TEST(regular_data_make_test, zero_plain)
{
    const std::filesystem::path zeroPlainFile(ZERO_PLAIN_INPUT);
    IrregularData irregularData(zeroPlainFile, true);

    ASSERT_TRUE(irregularData.Read());

    const std::filesystem::path output(OUTPUT"_zero_plain");
    RegularData regularData(output);

    ASSERT_TRUE(regularData.Make(irregularData));
    ASSERT_TRUE(regularData.Write());

    for(t_doses::const_iterator dose = regularData.Doses().cbegin(); dose != regularData.Doses().cend(); ++dose)
    {
        ASSERT_EQ(*dose, 0);
    }
}

TEST(regular_data_make_test, inclined_plain)
{
    const std::filesystem::path input(INCLINED_PLAIN_INPUT);
    IrregularData irregularData(input, true);

    ASSERT_TRUE(irregularData.Read());

    const std::filesystem::path output(OUTPUT"_inclined_plain");
    RegularData regularData(output);

    ASSERT_TRUE(regularData.Make(irregularData));
    ASSERT_TRUE(regularData.Write());

    t_coordinates::const_iterator centerNode = std::find(regularData.Coordinates().cbegin(),
        regularData.Coordinates().cend(), t_point({0, 0}));
    ASSERT_NE(centerNode, regularData.Coordinates().cend());
    size_t centerIndex = std::distance(regularData.Coordinates().cbegin(), centerNode);
    ASSERT_EQ(regularData.Doses().at(centerIndex), 2);
}