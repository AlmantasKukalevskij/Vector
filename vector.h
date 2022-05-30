#pragma once
#include <iostream>
#include <assert.h>
#include <limits>
#include <string>

using std::cout;
using std::endl;

template <typename T>
class customVector
{
public:
    typedef T value_type;
    typedef size_t size_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

private:
    iterator v_Data = nullptr;
    size_type v_size = 0;
    size_type v_capacity = 0;

    void alloc_new()
    {
        T* old = v_Data;
        //delete[] v_Data;
        v_capacity = v_capacity * 2 + 1;
        v_Data = new T[v_capacity];
        std::copy(old, old + v_size, v_Data);
        delete[] old;
    }

public:
    customVector() {};
    customVector(const customVector& other)
    {
        this->v_size = other.v_size;
        this->v_capacity = other.v_capacity;
        this->v_Data = new value_type[v_size];
        for (size_type i = 0; i < v_size; i++)
            v_Data[i] = other.v_Data[i];
    }
    customVector(customVector&& other)
    {
        this->v_size = other.v_size;
        this->v_capacity = other.v_capacity;
        this->v_Data = new value_type[v_size];
        v_Data = other.v_Data;
        other.v_Data = nullptr;
    }
    customVector& operator=(const customVector& other)
    {
        if (&other == this)
            return *this;
        this->v_size = other.v_size;
        this->v_capacity = other.v_capacity;
        this->v_Data = new value_type[v_size];
        std::copy(other.begin(), other.end(), v_Data);
        return *this;
    }
    customVector& operator=(customVector&& other)
    {
        if (other == this)
            return *this;
        this->v_size = other.v_size;
        this->v_capacity = other.v_capacity;
        this->v_Data = new value_type[v_size];
        this->v_Data = other.v_Data;
        other.v_Data = nullptr;
        return *this;
    }
    ~customVector()
    {
        clear();
        ::operator delete(v_Data, v_capacity * sizeof(T));
    };
    void assign(size_type count, const value_type& value)
    {
        this->v_capacity = count;
        this->v_size = count;
        this->v_Data = new value_type[count];
        for (size_type i = 0; i < count; i++)
            v_Data[i] = value;
    }

    reference at(size_type pos)
    {
        if (pos >= v_size)
            throw std::out_of_range("out of boundries (v_size: " + std::to_string(v_size) + ", pos: " + std::to_string(pos) + ")");
        return v_Data[pos];
    }
    const_reference at(size_type pos) const
    {
        if (pos >= v_size)
            throw std::out_of_range("out of boundries (v_size: " + std::to_string(v_size) + ", pos: " + std::to_string(pos) + ")");
        return v_Data[pos];
    }
    reference operator[](size_type i)
    {
        return v_Data[i];
    }
    const_reference operator[](size_type i) const
    {
        return v_Data[i];
    }
    reference front()
    {
        if (v_size == 0)
            throw std::invalid_argument("customVector is empty");
        return v_Data[0];
    }
    const_reference front() const
    {
        if (v_size == 0)
            throw std::invalid_argument("customVector is empty");
        return v_Data[0];
    }
    reference back()
    {
        if (v_size == 0)
            throw std::invalid_argument("customVector is empty");
        return v_Data[v_size - 1];
    }
    const_reference back() const
    {
        if (v_size == 0)
            throw std::invalid_argument("customVector is empty");
        return v_Data[v_size - 1];
    }
    iterator data()
    {
        return v_Data;
    }
    const_iterator data() const
    {
        return v_Data;
    }

    iterator begin()
    {
        return v_Data;
    }
    const_iterator begin() const
    {
        return v_Data;
    }
    iterator end()
    {
        return v_Data + v_size;
    }
    const_iterator end() const
    {
        return v_Data + v_size;
    }
    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }
    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const
    {
        return reverse_iterator(begin());
    }

    bool empty() const
    {
        return v_size == 0;
    }
    size_type size() const
    {
        return v_size;
    }
    void reserve(size_type new_cap)
    {
        if (new_cap > this->v_capacity)
            this->v_capacity = new_cap;
    }
    size_type capacity() const
    {
        return this->v_capacity;
    }
    void shrink_to_fit()
    {
        if (v_size < v_capacity)
            alloc_new();
        v_capacity = v_size;
    }

    void clear()
    {
        if (v_Data)
        {
            for (size_type i = 0; i < v_size; i++)
                v_Data[i].~T();
        }
        v_size = 0;
    }
    iterator insert(iterator pos, const_reference value)
    {
        if (pos > end() || pos < begin())
            throw std::out_of_range("Out of range");
        if (v_size >= v_capacity)
            alloc_new();
        v_size++;
        iterator new_data = new value_type[v_capacity];

        iterator last = std::move(begin(), pos, new_data);
        *last = value;
        std::move(pos, end(), last + 1);

        v_Data = new_data;
        return last;
    }
    iterator insert(iterator pos, size_type count, const_reference value)
    {
        if (count == 0)
            return pos;
        if (pos > end() || pos < begin())
            throw std::out_of_range("Out of range");
        v_size += count;
        if (v_size > v_capacity)
            alloc_new();
        iterator new_data = new value_type[v_capacity];

        iterator last = std::move(begin(), pos, new_data);
        for (size_type i = 0; i < count; i++)
            *(last + i) = value;
        std::move(pos, end(), last + count);

        v_Data = new_data;
        return last;
    }
    iterator erase(iterator pos)
    {
        std::move(pos + 1, end(), v_Data + std::distance(v_Data, pos));
        v_size--;
        return pos;
    }
    iterator erase(iterator first, iterator last)
    {
        std::move(last, end(), v_Data + std::distance(v_Data, first));
        v_size -= std::distance(first, last);
        return first;
    }
    void push_back(const_reference val)
    {
        if (v_size >= v_capacity)
            alloc_new();
        new (&v_Data[v_size++]) T(val);
    }
    void push_back(value_type&& val)
    {
        if (v_size >= v_capacity)
            alloc_new();
        new (&v_Data[v_size++]) T(val);
    }
    template <typename... Args>
    void emplace_back(Args &&...args)
    {
        if (v_size >= v_capacity)
            alloc_new();
        new (&v_Data[v_size++]) T(args...);
    }
    void pop_back()
    {
        if (v_size > 0)
        {
            --v_size;
            v_Data[v_size].~T();
        }
    }
    void resize(size_type count)
    {
        if (count < 0)
            throw std::invalid_argument("Invalid argument");
        if (count > v_size)
        {
            alloc_new();
            for (size_type i = v_size; i < count; i++)
                ::new (&v_Data[i]) T();
        }
        else if (count < v_size)
        {
            for (size_type i = count + 1; i <= v_size; i++)
                v_Data[i].~T();
        }
        v_size = count;
    }
    void swap(customVector& other)
    {
        iterator temp;
        temp = this->v_Data;
        this->v_Data = other.v_Data;
        other.v_Data = temp;

        size_type tempS = this->v_size;
        this->v_size = other.v_size;
        other.v_size = tempS;

        tempS = this->v_capacity;
        this->v_capacity = other.v_capacity;
        other.v_capacity = tempS;
    }

    bool operator==(const customVector& other) const
    {
        if (v_size != other.v_size)
            return false;

        for (size_type i = 0; i < v_size; i++)
            if (v_Data[i] != other.v_Data[i])
                return false;

        return true;
    }
    bool operator!=(const customVector& other) const
    {
        if (v_size != other.v_size)
            return true;

        for (size_type i = 0; i < v_size; i++)
            if (v_Data[i] != other.v_Data[i])
                return true;

        return false;
    }
    bool operator<(const customVector& other) const
    {
        for (size_type i = 0; i < std::min(v_size, other.size()); i++)
            if (at(i) != other.at(i))
                return (at(i) < other.at(i));
        if (v_size < other.size())
            return true;
        return false;
    }
    bool operator>(const customVector& other) const
    {
        for (size_type i = 0; i < std::min(v_size, other.size()); i++)
            if (at(i) != other.at(i))
                return (at(i) > other.at(i));
        if (v_size > other.size())
            return true;
        return false;
    }
    bool operator<=(const customVector& other) const
    {
        for (size_type i = 0; i < std::min(v_size, other.size()); i++)
            if (at(i) != other.at(i))
                return (at(i) < other.at(i));
        if (v_size <= other.size())
            return true;
        return false;
    }
    bool operator>=(const customVector& other) const
    {
        for (size_type i = 0; i < std::min(v_size, other.size()); i++)
            if (at(i) != other.at(i))
                return (at(i) > other.at(i));
        if (v_size >= other.size())
            return true;
        return false;
    }
};