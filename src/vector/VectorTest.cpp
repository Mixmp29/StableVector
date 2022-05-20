#include <vector/StableVector.hpp>

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace StabVec {

template <typename T, typename U>
void catch_error(std::string& error, U func)
{
    try {
        return func;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << '\n';
        error = func.what();
    }
}

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

TEST(TimeSuite, TestEmpty)
{
    StableVector<int> vec1;
    const StableVector<int> vec2 = {1, 2};
    std::pair<bool, bool> expect(true, false);
    std::pair<bool, bool> result(vec1.empty(), vec2.empty());
    EXPECT_EQ(expect, result);
}

TEST(TimeSuite, TestSquareBrackets)
{
    const StableVector<int> vec2 = {1, 2};
    const int expect = 2;
    const int result = vec2[1];
    EXPECT_EQ(expect, result);
}

} // namespace StabVec