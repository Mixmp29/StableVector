#pragma once

#include <cmath>
#include <iostream>

template <typename T>
class StableVector {
public:
private:
    T* elements = nullptr;
    T* first_free = nullptr;
    T* cap = nullptr;
};
