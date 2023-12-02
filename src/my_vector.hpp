#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP
#include <unistd.h>
#include <iostream>
#include <cassert>

template <typename T>
class my_vector
{
private:
    static const size_t INIT_SIZE = 15; // 初始化大小
    static constexpr double INCREMENT_SIZE = 1.5;  //只有静态常量（整型）数据成员才可以在类中初始化

public:
    my_vector(const int s = 0)
    {
        size_t len = s > INCREMENT_SIZE ? s : INCREMENT_SIZE;
        _ptr = new T[len];
        _size = 0;
        _capacity = len;
    }

    my_vector(const my_vector &other):_size(other._size),_capacity(other._capacity)
    {
        _ptr = new T[_capacity];
        for(int i = 0; i < _size; ++i)
        {
            _ptr[i] = other[i];
        }
    }

    ~my_vector()
    {
        delete[] _ptr;
        _ptr = nullptr;
        _size = _capacity = 0;
    }

public:
    const T &at(const size_t index) const // 同时进行越界检查
    {
        assert(index >= 0 && index < _size);
        return _ptr[index];
    }

    T &operator[](const size_t index) const
    {
        return _ptr[index];
    }

    T &operator=(const my_vector &other) //
    {
        _size = other._size;
        _capacity = other._capacity;
        _ptr = new T[_capacity];
        for(int i = 0; i < _size; ++i)
        {
            _ptr[i] = other[i];
        }
    }

    T &front() const
    {
        assert(!empty());
        return _ptr[0];
    }

    T &back() const
    {
        assert(!empty());
        return _ptr[_size - 1];
    }

    T *data() const
    {
        return _ptr;
    }
    bool empty() const
    {
        return _size == 0;
    }

    int size() const
    {
        return _size;
    }

    int max_size() const
    {
        return _capacity - _size;
    }

    void reserver(const int len)
    {
        if (len <= _size)
            return;

        delete[] _ptr;
        _ptr = new T[len];
        _capacity = len;
    }

    size_t capacity() const
    {
        return _capacity;
    }

    void clear()
    {
        delete[] _ptr;
        _size = 0;
    }

    void insert(const int index, const T val)
    {
        if (index < 0 || index > _size)
            return; // 假如越界就退出
        if (_size == _capacity)
        {
            increment();
        }

        for (int i = _size - 1; i >= index; --i)
        {
            _ptr[i + 1] = _ptr[i];
        }

        _ptr[index] = val;
    }

    void erase(const int i, const int sign = 0) // 0按下标删 1按第一个值删
    {
        assert(i >= 0 && i < _size);
        if (sign == 0)
        {
            for (int i = i + 1; i < _size; ++i)
            {
                _ptr[i - 1] = _ptr[i];
            }
        }
        else if (sign == 1)
        {
            for (int i = 0; i < _size; ++i)
            {
                if (_ptr[i] == i)
                {
                    for (int j = i + 1; j < _size; ++j)
                    {
                        _ptr[j - 1] = _ptr[j];
                    }
                    break;
                }
            }
        }
    }

    void push_back(const T val)
    {
        if (_size == _capacity)
            increment();

        _ptr[_size] = val;
        _size++;
    }

    void pop_back()
    {
        assert(_size > 0);

        _size--;
    }

    void resize(const size_t len)
    {
        reserve(len);
        _size = len;
    }

    void reserve(const size_t len)
    {
        if(len <= _capacity) return;
        
        T* t = _ptr;
        _ptr = new T[len];
        _capacity = len;
        for(int i = 0; i < _size; ++i)
        {
            _ptr[i] = t[i];
        }
        delete[] t;
    }

    void swap(my_vector &other) //
    {
        std::swap(_ptr, other._ptr);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }
private:
    void increment()
    {
        T *tmp = _ptr;
        int len = _capacity * INCREMENT_SIZE;
        _ptr = new T[len];
        for (int i = 0; i < _size; ++i)
        {
            _ptr[i] = tmp[i];
        }
        _capacity = len;
        delete[] tmp;
    }

private:
    T *_ptr;
    size_t _size;
    size_t _capacity;
};
#endif