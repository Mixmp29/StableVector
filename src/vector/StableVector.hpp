#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <utility>

namespace StabVec {

template <typename T>
class StableVector {
private:
    struct Node {
        Node() = default;
        Node(T val) : /* ptr(new T[1]),  */ value(val){};
        /*         ~Node() noexcept
                {
                    delete ptr;
                } */

        // T* ptr = nullptr;
        T value = T();
    };

    void chk_n_alloc()
    {
        if (first_free == cap)
            reallocate();
    }
    std::pair<Node*, Node*> alloc_n_copy(const Node*, const Node*);
    void free();
    void reallocate();

    Node* elements = nullptr;
    Node* first_free = nullptr;
    Node* cap = nullptr;

public:
    template <typename U, typename G>
    struct GenericIterator {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = G;
        using pointer = G*;
        using reference = G&;

        GenericIterator(U* pointer, size_t i) : ptr(pointer), index(i)
        {
        }

        reference operator*()
        {
            return (ptr)[index].value;
        }

        pointer operator->() const
        {
            return (ptr)[index].value;
        }

        GenericIterator& operator++()
        {
            ++index;
            return *this;
        }

        GenericIterator& operator++(int)
        {
            GenericIterator tmp = *this;
            ++index;
            return tmp;
        }

        GenericIterator& operator--()
        {
            --index;
            return *this;
        }

        GenericIterator& operator--(int)
        {
            GenericIterator tmp = *this;
            --index;
            return tmp;
        }

        GenericIterator& operator+=(size_t i)
        {
            index += i;
            return *this;
        }

        GenericIterator operator+(size_t i)
        {
            GenericIterator tmp = *this;
            tmp += i;
            return tmp;
        }

        GenericIterator& operator-=(size_t i)
        {
            index -= i;
            return *this;
        }

        GenericIterator operator-(size_t i)
        {
            GenericIterator tmp = *this;
            tmp -= i;
            return tmp;
        }

        friend bool
        operator==(const GenericIterator& lhs, const GenericIterator& rhs)
        {
            return lhs.index == rhs.index;
        }

        friend bool
        operator!=(const GenericIterator& lhs, const GenericIterator& rhs)
        {
            return lhs.index != rhs.index;
        }

        friend bool
        operator<(const GenericIterator& lhs, const GenericIterator& rhs)
        {
            return lhs.index < rhs.index;
        }

        friend bool
        operator>(const GenericIterator& lhs, const GenericIterator& rhs)
        {
            return lhs.index > rhs.index;
        }

        friend difference_type
        operator-(const GenericIterator& lhs, const GenericIterator& rhs)
        {
            return lhs.index - rhs.index;
        }

    private:
        U* ptr;
        size_t index;
    };

    using Iterator = GenericIterator<StableVector<T>::Node, T>;
    using ConstIterator = GenericIterator<const StableVector<T>::Node, const T>;

    StableVector() = default;
    StableVector(const StableVector&);
    StableVector(StableVector&&) noexcept;
    StableVector(std::initializer_list<T>);
    StableVector& operator=(const StableVector&);
    StableVector& operator=(StableVector&&) noexcept;
    StableVector& operator=(std::initializer_list<T>);
    ~StableVector() noexcept;

    void push_back(const T&);
    void push_back(T&&);
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
        if (n < size())
            return elements[n].value;
        else
            throw std::out_of_range("Out of bounds");
    }
    const T& operator[](size_t n) const
    {
        if (n < size())
            return elements[n].value;
        else
            throw std::out_of_range("Out of bounds");
    }

    Iterator begin()
    {
        return Iterator(elements, 0);
    }
    Iterator end()
    {
        return Iterator(elements, size());
    }

    ConstIterator begin() const
    {
        return ConstIterator(elements, 0);
    }
    ConstIterator end() const
    {
        return ConstIterator(elements, size());
    }
};

template <typename T>
inline StableVector<T>::StableVector(const StableVector& s)
{
    auto newdata = alloc_n_copy(s.elements, s.first_free);
    elements = newdata.first;
    first_free = cap = newdata.second;
}

template <typename T>
inline StableVector<T>::StableVector(StableVector&& s) noexcept
    : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}

template <typename T> // TODO: переделать под push_back()
inline StableVector<T>::StableVector(std::initializer_list<T> il)
    : elements(nullptr), first_free(nullptr), cap(nullptr)
{
    for (auto& val : il) {
        push_back(val);
    }
}

template <typename T>
inline StableVector<T>& StableVector<T>::operator=(const StableVector& rhs)
{
    auto data = alloc_n_copy(rhs.elements, rhs.first_free);
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
inline StableVector<T>& StableVector<T>::operator=(
        std::initializer_list<T> il) // TODO: переделать под push_back()
{
    elements = nullptr;
    first_free = nullptr;
    cap = nullptr;

    for (auto& val : il) {
        push_back(val);
    }
}

template <typename T>
inline bool operator==(const StableVector<T>& lhs, const StableVector<T>& rhs)
{
    if (lhs.size() == rhs.size()) {
        for (size_t i = 0; i < lhs.size(); ++i)
            if (lhs[i] == rhs[i])
                continue;
            else
                return false;
    } else
        return false;

    return true;
}

template <typename T>
inline bool operator!=(const StableVector<T>& lhs, const StableVector<T>& rhs)
{
    if (lhs.size() == rhs.size()) {
        for (size_t i = 0; i < lhs.size(); ++i)
            if (lhs[i] != rhs[i])
                continue;
            else
                return false;
    } else
        return false;

    return true;
}

template <typename T>
inline bool operator<(const StableVector<T>& lhs, const StableVector<T>& rhs)
{
    if (lhs.size() == rhs.size()) {
        for (size_t i = 0; i < lhs.size(); ++i)
            if (lhs[i] < rhs[i])
                continue;
            else
                return false;
    } else
        return false;

    return true;
}

template <typename T>
inline bool operator>(const StableVector<T>& lhs, const StableVector<T>& rhs)
{
    if (lhs.size() == rhs.size()) {
        for (size_t i = 0; i < lhs.size(); ++i)
            if (lhs[i] > rhs[i])
                continue;
            else
                return false;
    } else
        return false;

    return true;
}

template <typename T>
inline StableVector<T>::~StableVector() noexcept // TODO: возможно поменять
                                                 // освобождение
{
    // delete[] elements;
    free();
}

template <typename T>
inline void
StableVector<T>::push_back(const T& s) // TODO: переделать push_back()
{
    chk_n_alloc();
    new ((void*)first_free++) Node(s);
}

template <typename T>
inline void StableVector<T>::push_back(T&& s)
{
    chk_n_alloc();
    new ((void*)first_free++) Node(std::move(s));
}

template <typename T>
inline void StableVector<T>::reserve(size_t n) // поменять Node
{
    if (n > capacity()) {
        auto first = new Node[n];
        auto dest = first;
        auto elem = elements;

        for (size_t i = 0; i < size(); i++) {
            new ((void*)dest++) Node(std::move(*elem++));
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
inline std::pair<
        typename StableVector<T>::Node*,
        typename StableVector<T>::Node*>
StableVector<T>::alloc_n_copy(
        const Node* b,
        const Node* e) // поменять на Node в объявлении и в инициализации
{
    auto data = new Node[e - b];
    return {data, std::uninitialized_copy(b, e, data)};
}

template <typename T>
inline void StableVector<T>::free()
{
    // delete elements;
    delete[] elements;
}

template <typename T>
inline void StableVector<T>::reallocate() // Заменить на Node
{
    auto newcapacity = size() ? 2 * size() : 2;

    auto first = new Node[newcapacity];
    auto dest = first;
    auto elem = elements;

    for (size_t i = 0; i < size(); i++) {
        new ((void*)dest++) Node(std::move(*elem++));
    }

    free();

    elements = first;
    first_free = dest;
    cap = elements + newcapacity;
}

} // namespace StabVec