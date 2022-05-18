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

    Vec& operator=(std::initializer_list<T>);
    void push_back(const T&);
    void push_back(T&&);
    template <class... Args>
    void emplace_back(Args&&...);

    size_t size() const
    {
        return first_free - elements;
    }
    size_t capacity() const
    {
        return cap - elements;
    }
    bool empty() const
    {
        return elements == 0;
    }

    T& operator[](size_t n)
    {
        return elements[n];
    }
    const T& operator[](size_t n) const
    {
        return elements[n];
    }

private:
    T* elements = nullptr;
    T* first_free = nullptr;
    T* cap = nullptr;
};
