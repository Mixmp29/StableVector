#pragma once

#include <cmath>
#include <iostream>
#include <memory>

namespace StabVec {

template <typename T>
class StableVector {
public:
    StableVector() = default;
    StableVector(const StableVector&);
    StableVector(StableVector&&) noexcept;
    StableVector(std::initializer_list<T>);
    StableVector& operator=(const StableVector&);
    StableVector& operator=(StableVector&&) noexcept;
    ~StableVector() noexcept;

    StableVector& operator=(std::initializer_list<T>);
    void push_back(const T&);
    void push_back(T&&);
    template <class... Args>
    void emplace_back(Args&&...);
    void reserve(size_t n);
    void resize(size_t n, T val = T());

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
        if (n <= size())
            return elements[n];
        return elements[1];
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
    return {data, std::uninitialized_copy(b, e, data)};
}

template <typename T>
inline StableVector<T>::StableVector(StableVector&& s) noexcept
    : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}

template <typename T>
inline StableVector<T>::StableVector(const StableVector& s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

template <typename T>
inline StableVector<T>::StableVector(std::initializer_list<T> il)
{
    auto data = alloc_n_copy(il.begin(), il.end());

    free();

    elements = data.first;
    first_free = cap = data.second;
}

template <typename T>
inline void StableVector<T>::free()
{
    delete[] elements;
}

template <typename T>
inline StableVector<T>& StableVector<T>::operator=(std::initializer_list<T> il)
{
    auto data = alloc_n_copy(il.begin(), il.end());

    free();

    elements = data.first;
    first_free = cap = data.second;

    return *this;
}

template <typename T>
inline StableVector<T>& StableVector<T>::operator=(StableVector&& rhs) noexcept
{
    if (this != &rhs)
        free();

    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;

    rhs.elements = rhs.first_free = rhs.cap = nullptr;

    return *this;
}

template <typename T>
inline StableVector<T>& StableVector<T>::operator=(const StableVector& rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

template <typename T>
inline void StableVector<T>::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 2;

    auto first = new T[newcapacity];
    auto dest = first;
    auto elem = elements;

    for (size_t i = 0; i < size(); i++) {
        new ((void*)dest++) T(std::move(*elem++));
    }

    free();

    elements = first;
    first_free = dest;
    cap = elements + newcapacity;
}

template <typename T>
inline void StableVector<T>::reserve(size_t n)
{
    if (n > capacity()) {
        auto first = new T[n];
        auto dest = first;
        auto elem = elements;

        for (size_t i = 0; i < size(); i++) {
            new ((void*)dest++) T(std::move(*elem++));
        }

        free();

        elements = first;
        first_free = dest;
        cap = elements + n;
    }
}

template <typename T>
inline void StableVector<T>::resize(size_t n, T val)
{
    if (n < size()) {
        while (n < size())
            first_free--;
    } else {
        while (n != size())
            push_back(val);
    }
}

template <typename T>
inline void StableVector<T>::push_back(const T& s)
{
    chk_n_alloc();
    new ((void*)first_free++) T(s);
}

template <typename T>
inline void StableVector<T>::push_back(T&& s)
{
    chk_n_alloc();
    new ((void*)first_free++) T(std::move(s));
}

template <typename T>
template <class... Args>
inline void StableVector<T>::emplace_back(Args&&... args)
{
    chk_n_alloc();
    new ((void*)first_free++) T(std::forward<Args>(args)...);
}

} // namespace StabVec