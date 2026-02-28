#pragma once
#include <iostream>
#include <stdexcept>

// This Class Demonstrates the usage of String Class.
// There is a built-in class in C++ called std::string.
// However , we make our own using char arrays.
// While making we should keep many things in mind like '\0' etc.

// std::string in C++ is of 32 bytes from start.
// It has 3 things in it :
// 1) char pointer * to hold data , 2) size_t , 3) capacity = 24 bytes (On 64 Bit System) , may vary for others but pointer in modern days is 8 bytes now.
// Compilers add a buffer for Small String Optimization (SSO).
// On a 64-bit system, the string object is padded to 32 bytes to keep memory alignment efficient.
// The Object itself (its data members) is on stack but data being pointed may or may not be in heap.
// If 15-22 chars then data in stack otherwise heap.

// Here in our class , the data being stored will be in heap whether any kind of length.
// The Size / Bytes of our std::string or our class String has fixed object size.
// On stack it has fixed *data , capacity and size variables.
// The thing growing its characters is in heap which is not visible to us but we can see by .size() or .length() or .capacity() methods.
class String
{
private:
    char *_data;
    size_t _size;
    size_t _capacity;

    // --- MANUAL INTERNAL HELPERS ---
    size_t get_len(const char *s) const
    {
        if (!s)
            return 0;
        size_t len = 0;
        while (s[len] != '\0')
            len++;
        return len;
    }

    void copy_raw(char *dest, const char *src, size_t n)
    {
        for (size_t i = 0; i < n; i++)
            dest[i] = src[i];
        dest[n] = '\0';
    }

public:
    static const size_t npos = -1;

    // 1. Default Constructor
    String() : _size(0), _capacity(16)
    {
        _data = new char[_capacity];
        _data[0] = '\0';
    }

    // 2. C-String Constructor (O(n))
    String(const char *s)
    {
        _size = get_len(s);
        _capacity = _size + 16;
        _data = new char[_capacity];
        copy_raw(_data, s, _size);
    }

    // 3. Buffer Constructor (O(n)) - Takes first 'n' chars from a char array
    String(const char *s, size_t n) : _size(n), _capacity(n + 1)
    {
        _data = new char[_capacity];
        for (size_t i = 0; i < n; i++)
            _data[i] = s[i];
        _data[_size] = '\0';
    }

    // 4. Fill Constructor (O(n)) - String s(10, 'A') -> "AAAAAAAAAA"
    String(size_t n, char c) : _size(n), _capacity(n + 1)
    {
        _data = new char[_capacity];
        for (size_t i = 0; i < n; i++)
            _data[i] = c;
        _data[_size] = '\0';
    }

    // 5. Single Char Constructor
    // Here explicit keyword allows user not to pass any int , or a string as char can accept that
    // Its just for a single char input.
    explicit String(char c) : _size(1), _capacity(16)
    {
        _data = new char[_capacity];
        _data[0] = c;
        _data[1] = '\0';
    }

    // 6. Copy Constructor (Rule of 5 - Deep Copy)
    String(const String &other) : _size(other._size), _capacity(other._size + 1)
    {
        _data = new char[_capacity];
        copy_raw(_data, other._data, _size);
    }

    // 7. Move Constructor (Rule of 5 - Shallow Copy/Steal)
    String(String &&other) noexcept
        : _data(other._data), _size(other._size), _capacity(other._capacity)
    {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    // --- DESTRUCTOR ---
    ~String() { delete[] _data; }

    // --- ASSIGNMENT OPERATORS ---
    String &operator=(const String &other)
    {
        if (this != &other)
        {
            char *new_buf = new char[other._size + 1];
            copy_raw(new_buf, other._data, other._size);
            delete[] _data;
            _data = new_buf;
            _size = other._size;
            _capacity = _size + 1;
        }
        return *this;
    }

    String &operator=(String &&other) noexcept
    {
        if (this != &other)
        {
            delete[] _data;
            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;
            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    // --- ELEMENT ACCESS (Bounds Checked) ---
    char &operator[](size_t idx) { return _data[idx]; }
    const char &operator[](size_t idx) const { return _data[idx]; }

    char &at(size_t idx)
    {
        if (idx >= _size)
            throw std::out_of_range("Index out of bounds");
        return _data[idx];
    }

    char &front() { return _data[0]; }
    char &back() { return _data[_size - 1]; }
    const char *c_str() const { return _data; }

    // --- CAPACITY & MODIFIERS ---
    size_t length() const { return _size; }
    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; } // Check this to see the "real" growth! ,
    // This capacity() function will tell you about the string's actual size being pointed by the _data pointer.

    bool empty() const { return _size == 0; }

    void reserve(size_t n)
    {
        if (n <= _capacity)
            return;
        char *temp = new char[n];
        copy_raw(temp, _data, _size);
        delete[] _data;
        _data = temp;
        _capacity = n;
    }

    void push_back(char c)
    {
        if (_size + 1 >= _capacity)
            reserve(_capacity * 2);
        _data[_size++] = c;
        _data[_size] = '\0';
    }

    void append(const String &str)
    {
        size_t n = _size + str._size;
        if (n >= _capacity)
            reserve(n + 1);
        for (size_t i = 0; i < str._size; i++)
            _data[_size + i] = str._data[i];
        _size = n;
        _data[_size] = '\0';
    }

    void insert(size_t pos, const char *s)
    {
        if (pos > _size)
            throw std::out_of_range("Insert error");
        size_t slen = get_len(s);
        if (_size + slen >= _capacity)
            reserve(_size + slen + 1);
        for (int i = (int)_size; i >= (int)pos; i--)
            _data[i + slen] = _data[i];
        for (size_t i = 0; i < slen; i++)
            _data[pos + i] = s[i];
        _size += slen;
    }

    void erase(size_t pos, size_t len)
    {
        if (pos >= _size)
            throw std::out_of_range("Erase error");
        if (pos + len > _size)
            len = _size - pos;
        for (size_t i = pos; i <= _size - len; i++)
            _data[i] = _data[i + len];
        _size -= len;
    }

    // --- SEARCH & SUBSTRING ---
    String substr(size_t pos, size_t len = npos) const
    {
        if (pos >= _size)
            throw std::out_of_range("Substr error");
        if (len == npos || pos + len > _size)
            len = _size - pos;
        return String(_data + pos, len); // Uses Constructor #3
    }

    size_t find(const char *s, size_t pos = 0) const
    {
        size_t slen = get_len(s);
        if (slen == 0)
            return pos;
        for (size_t i = pos; i <= (int)_size - (int)slen; i++)
        {
            size_t j = 0;
            while (j < slen && _data[i + j] == s[j])
                j++;
            if (j == slen)
                return i;
        }
        return npos;
    }

    // --- CONVERSIONS (STRICT VALIDATION) ---
    static int stoi(const String &s)
    {
        if (s.empty())
            throw std::invalid_argument("stoi: empty");
        long long res = 0;
        int sign = 1, i = 0;
        if (s[0] == '-')
        {
            sign = -1;
            i = 1;
        }
        for (; i < s._size; i++)
        {
            if (s[i] < '0' || s[i] > '9')
                throw std::invalid_argument("stoi: invalid char");
            res = res * 10 + (s[i] - '0');
        }
        return (int)(res * sign);
    }

    static String to_string(int val)
    {
        if (val == 0)
            return String("0");
        char buf[12];
        int i = 0;
        long long n = (val < 0) ? -(long long)val : val;
        while (n > 0)
        {
            buf[i++] = (n % 10) + '0';
            n /= 10;
        }
        if (val < 0)
            buf[i++] = '-';
        buf[i] = '\0';
        for (int j = 0; j < i / 2; j++)
        {
            char t = buf[j];
            buf[j] = buf[i - j - 1];
            buf[i - j - 1] = t;
        }
        return String(buf);
    }

    // --- OPERATORS ---
    bool operator==(const String &other) const
    {
        if (_size != other._size)
            return false;
        for (size_t i = 0; i < _size; i++)
            if (_data[i] != other._data[i])
                return false;
        return true;
    }

    friend std::ostream &operator<<(std::ostream &os, const String &s)
    {
        os << s._data;
        return os;
    }

    class Iterator
    {
    private:
        char *ptr;   // Current position
        char *start; // Boundary: First character
        char *limit; // Boundary: Null terminator (one-past-the-last)

    public:
        // Constructor now takes the range of the string
        Iterator(char *p, char *s, char *l) : ptr(p), start(s), limit(l) {}

        // Safe Dereference
        char &operator*()
        {
            if (ptr < start || ptr >= limit)
            {
                throw std::out_of_range("Iterator dereference out of bounds!");
            }
            return *ptr;
        }

        // Safe Increment
        Iterator &operator++()
        {
            if (ptr >= limit)
            {
                throw std::out_of_range("Iterator cannot increment past end!");
            }
            ptr++;
            return *this;
        }

        // Safe Jump (it + n)
        Iterator operator+(int n) const
        {
            if (ptr + n > limit || ptr + n < start)
            {
                throw std::out_of_range("Iterator jump out of bounds!");
            }
            return Iterator(ptr + n, start, limit);
        }

        // Relational operators
        bool operator!=(const Iterator &other) const { return ptr != other.ptr; }
        bool operator==(const Iterator &other) const { return ptr == other.ptr; }

        // Distance
        long long operator-(const Iterator &other) const { return ptr - other.ptr; }
    };

    // --- UPDATED MEMBER FUNCTIONS ---

    Iterator begin()
    {
        // Passes the start (_data) and the limit (_data + _size) to the iterator
        return Iterator(_data, _data, _data + _size);
    }

    Iterator end()
    {
        // Still points to the end, but knows the boundaries
        return Iterator(_data + _size, _data, _data + _size);
    }
};