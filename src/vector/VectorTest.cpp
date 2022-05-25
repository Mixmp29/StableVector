#include <vector/StableVector.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace StabVec {

TEST(Vector, TestSize)
{
    const StableVector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    const int expect = 8;
    const int result = vec.size();
    EXPECT_EQ(expect, result);
}

TEST(Vector, TestCpapcity)
{
    const StableVector<int> vec = {1, 2, 3, 4, 5, 6};
    const int expect = 6;
    const int result = vec.capacity();
    EXPECT_EQ(expect, result);
}

TEST(Vector, TestCpapcity2)
{
    const int a = 1;
    const int b = 2;
    const int c = 3;
    StableVector<int> vec = {a, b};
    vec.push_back(c);
    const int expect = 4;
    const int result = vec.capacity();
    EXPECT_EQ(expect, result);
}

TEST(Vector, TestEmpty)
{
    StableVector<int> vec1;
    const StableVector<int> vec2 = {1, 2};
    std::pair<bool, bool> expect(true, false);
    std::pair<bool, bool> result(vec1.empty(), vec2.empty());
    EXPECT_EQ(expect, result);
}

TEST(Vector, TestSquareBrackets)
{
    const StableVector<int> vec = {1, 2};
    const int expect = 2;
    const int result = vec[1];
    EXPECT_EQ(expect, result);
}

TEST(Vector, OutOfRange)
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

TEST(Vector, TestBeginEnd)
{
    StableVector<std::string> vec = {"test ", "string ", "here"};
    const std::string expect = "test string here";
    std::string result;
    for (auto i = vec.begin(); i < vec.end(); ++i) {
        result += *i;
    }
    EXPECT_EQ(expect, result);
}

TEST(Vector, TestSort)
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

TEST(Vector, TestSort2)
{
    const int a = 6;
    const int b = 2;
    const int c = 1;
    const int d = 0;
    StableVector<int> result1 = {a, b, c, d};
    StableVector<int> result2 = {d, c, b, a};
    const StableVector<int> expect = {0, 1, 2, 6};
    std::sort(result1.begin(), result2.end());
    EXPECT_EQ(expect, result1);
}

TEST(Vector, TestSwap)
{
    const int a = 6;
    const int b = 2;
    const int c = 1;
    const int d = 0;
    StableVector<int> result = {a, b, c, d};
    const StableVector<int> expect = {6, 0, 1, 2};
    std::cout << "size(): " << result.size() << std::endl;
    std::swap(result[1], result[3]);
    EXPECT_EQ(expect, result);
}

TEST(Vector, TestFor)
{
    const int a = 6;
    const int b = 2;
    const int c = 1;
    const int d = 0;
    StableVector<int> result = {a, b, c, d};
    StableVector<int> expect;
    for (auto& i : result) {
        expect.push_back(i);
        std::cout << i << std::endl;
    }
    EXPECT_EQ(expect, result);
}

TEST(Vector, TestFind)
{
    const int a = 6;
    const int b = 2;
    const int c = 1;
    const int d = 0;
    const StableVector<int> vec = {a, b, c, d};
    const int expect = 6;
    auto result = std::find(vec.begin(), vec.end() - 1, expect);
    EXPECT_EQ(expect, *result);
}

TEST(Vector, TestPushBack)
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

TEST(Vector, TestReserve)
{
    const int a = 1;
    const int b = 2;
    const int c = 3;
    StableVector<int> vec = {a, b, c};
    const size_t new_cap = 7;
    vec.reserve(new_cap);
    const size_t expect = 7;
    const size_t result = vec.capacity();
    EXPECT_EQ(expect, result);
}

TEST(Vector, TestResize)
{
    const int a = 1;
    const int b = 2;
    const int c = 3;
    StableVector<int> vec = {a, b, c};
    const size_t new_size = 8;
    vec.resize(new_size);
    const size_t expect = 8;
    const size_t result = vec.size();
    EXPECT_EQ(expect, result);
}

TEST(Vector, TestResizeSmaller)
{
    const int a = 1;
    const int b = 2;
    const int c = 3;
    const int d = 4;
    StableVector<int> vec = {a, b, c, d};
    const size_t new_size = 2;
    vec.resize(new_size);
    const size_t expect = 2;
    const size_t result = vec.size();
    EXPECT_EQ(expect, result);
}

TEST(Vector, TestVectors)
{
    StableVector<StableVector<int>> vec1;
    StableVector<StableVector<int>> vec2;
    vec1.push_back({1, 2, 3});
    vec1.push_back({3, 5, 8});
    vec2.push_back({1, 2, 3});
    vec2.push_back({3, 5, 8});
    EXPECT_EQ(vec1, vec2);
}

} // namespace StabVec