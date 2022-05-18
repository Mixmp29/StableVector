#pragma once

#include <cmath>
#include <iostream>

template <typename T>
class StableVector {
public:
    StableVector() = default;
    StableVector(const StableVector&);
    StableVector(StableVector&&) noexcept;
    StableVector& operator=(const StableVector&);
    StableVector& operator=(StableVector&&) noexcept;
    ~StableVector() noexcept;

    StableVector& operator=(std::initializer_list<T>);
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

    T* begin() const
    {
        return elements;
    }
    T* end() const
    {
        return first_free;
    }

private:
    void chk_n_alloc()
    {
        if (first_free == cap)
            reallocate();
    }
    std::pair<T*, T*> alloc_n_copy(const T*, const T*);
    void free();
    void reallocate();

    T* elements = nullptr;
    T* first_free = nullptr;
    T* cap = nullptr;
};

template <typename T>
inline StableVector<T>::~StableVector() noexcept
{
    free();
}

template <typename T>
inline std::pair<T*, T*> StableVector<T>::alloc_n_copy(const T* b, const T* e)
{
    auto data = new T[e - b];
    return {data, uninitialized_copy(b, e, data)};
}

template <typename T>
inline StableVector<T>::StableVector(StableVector&& s) noexcept
    : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}