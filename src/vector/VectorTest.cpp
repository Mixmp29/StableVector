#include <vector/StableVector.hpp>

#include <gtest/gtest.h>

#include <string>

namespace StabVec {

TEST(TimeSuite, PushBack)
{
    StableVector<int> vec5;
    vec5.push_back(1);
    int expect = 1;
    int result = vec5[0];
    EXPECT_EQ(expect, result);
}

} // namespace StabVec