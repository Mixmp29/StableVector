#pragma once

#include <cmath>
#include <iostream>

template <typename T>
class StableVector {
public:
    Vec() = default;
    Vec(const Vec&);
    Vec(Vec&&) noexcept;
    Vec& operator=(const Vec&);
    Vec& operator=(Vec&&) noexcept;
    ~Vec() noexcept;

private:
    T* elements = nullptr;
    T* first_free = nullptr;
    T* cap = nullptr;
};
