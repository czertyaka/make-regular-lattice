#include <gtest/gtest.h>
#include <array>

#include "data.hpp"

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