#include <vector/StableVector.hpp>

#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <vector>

namespace StabVec {

/* template <typename T, typename U>
void catch_error(std::vector<T>& errors, U func)
{
    try {
        func;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << '\n';
        errors.emplace_back();
    }
} */

TEST(TimeSuite, TestSize)
{
    const StableVector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    const int expect = 8;
    const int result = vec.size();
    EXPECT_EQ(expect, result);
}

TEST(TimeSuite, TestCpapcity)
{
    const StableVector<int> vec = {1, 2, 3, 4, 5, 6};
    const int expect = 6;
    const int result = vec.capacity();
    EXPECT_EQ(expect, result);
}

} // namespace StabVec