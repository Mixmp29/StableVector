#include <vector/StableVector.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace StabVec {

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
    const StableVector<int> vec = {1, 2};
    const int expect = 2;
    const int result = vec[1];
    EXPECT_EQ(expect, result);
}

TEST(TimeSuite, OutOfRange)
{
    const StableVector<int> vec = {1, 2};
    const std::string expect = "Out of bounds";
    const int index = 5;
    std::string result;
    try {
        vec[index];
    } catch (const std::out_of_range& err) {
        result = err.what();
    }
    EXPECT_EQ(expect, result);
}

TEST(TimeSuite, TestBeginEnd)
{
    StableVector<std::string> vec = {"test ", "string ", "here"};
    const std::string expect = "test string here";
    std::string result;
    for (auto i = vec.begin(); i < vec.end(); ++i) {
        result += *i;
    }
    EXPECT_EQ(expect, result);
}

TEST(TimeSuite, TestSort)
{
    const int a = 6;
    const int b = 2;
    const int c = 1;
    const int d = 0;
    StableVector<int> result = {a, b, c, d};
    const StableVector<int> expect = {0, 1, 2, 6};
    std::sort(result.begin(), result.end());
    EXPECT_EQ(expect, result);
}

TEST(TimeSuite, TestPushBack)
{
    StableVector<int> vec;
    const int a = 5;
    const int b = 7;
    const int c = 3;
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(c);
    const StableVector expect = {5, 7, 3};
    EXPECT_EQ(expect, vec);
}

TEST(TimeSuite, TestReserve)
{
    const int a = 1;
    const int b = 2;
    const int c = 3;
    StableVector vec = {a, b, c};
    const size_t new_cap = 7;
    vec.reserve(new_cap);
    const size_t expect = 7;
    const size_t result = vec.capacity();
    EXPECT_EQ(expect, result);
}

TEST(TimeSuite, TestResize)
{
    const int a = 1;
    const int b = 2;
    const int c = 3;
    StableVector vec = {a, b, c};
    const size_t new_size = 8;
    vec.resize(new_size);
    const size_t expect = 8;
    const size_t result = vec.size();
    EXPECT_EQ(expect, result);
}

TEST(TimeSuite, TestResizeSmaller)
{
    const int a = 1;
    const int b = 2;
    const int c = 3;
    const int d = 4;
    StableVector vec = {a, b, c, d};
    const size_t new_size = 2;
    vec.resize(new_size);
    const size_t expect = 2;
    const size_t result = vec.size();
    EXPECT_EQ(expect, result);
}

} // namespace StabVec