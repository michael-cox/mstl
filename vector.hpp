/*
 * Michael Cox
 * Vector Implementation
 * File: vector.hpp
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>
#include <cstring>
#include <iostream>
#include <cassert>
#include <exception>

namespace mstl
{
    template<typename T>
        class Vector
        {
            public:
                class iterator
                {
                    public:

                        iterator() { _data = nullptr; }

                        iterator(T *  data) { _data = data; }

                        iterator & operator++()
                        {
                            this->_data++;
                            return (*this);
                        }

                        iterator & operator--() {
                            this->_data--;
                            return (*this);
                        }

                        iterator & operator=(iterator & value)
                        {
                            this->_data = value._data;
                            return (*this);
                        }

                        const bool operator!=(const iterator & value) 
                        { return _data != value._data; }

                        T & operator*() const { return *_data; }

                    private:
                        T * _data;
                };

                Vector() : _capacity(0), _size(0), _data(nullptr) {}

                Vector(std::size_t size) : _capacity(size), _size(size) {
                    if(size ==0) { _data = nullptr; return; }
                    try {
                        _data = new T[_size];
                    }
                    catch(const std::exception &e) {
                        std::cout << "Standard excepton: " << e.what() << std::endl;
                    }
                }

                Vector(std::size_t size, const T & defaultValue) : _capacity(size), _size(size) {
                    if(size == 0) { _data = nullptr; return; }
                    try {
                        _data = new T[_size];
                    }
                    catch(const std::exception &e) {
                        std::cout << "Standard excepton: " << e.what() << std::endl;
                    }
                    for(std::size_t index = 0; index < size; ++index)
                        std::memcpy(_data + index, &defaultValue, sizeof(T));
                }

                Vector(Vector<T> & vectorToCopy) {
                    _capacity = vectorToCopy._capacity;
                    _size = vectorToCopy._size;
                    try {
                        _data = new T[_capacity];
                    }
                    catch(const std::exception &e) {
                        std::cout << "Standard excepton: " << e.what() << std::endl;
                    }
                    std::memcpy(_data, vectorToCopy._data, _size*sizeof(T));
                }

                Vector<T> & operator=(Vector<T> & vectorToCopy) {
                    if(_capacity) delete [] _data;
                    _capacity = vectorToCopy._capacity;
                    _size = vectorToCopy._size;
                    try {
                        _data = new T[_capacity];
                    }
                    catch(const std::exception &e) {
                        std::cout << "Standard excepton: " << e.what() << std::endl;
                    }
                    std::memcpy(_data, vectorToCopy._data, _size*sizeof(T));
                }

                Vector(Vector<T> && vectorToMove) : _size(vectorToMove._size),
                _capacity(vectorToMove._capacity), _data(vectorToMove._data) {
                    vectorToMove._capacity = 0;
                    vectorToMove._size = 0;
                    vectorToMove._data = nullptr;
                }

                Vector<T> &operator=(Vector<T> && vectorToMove) {
                    _capacity = vectorToMove._capacity;
                    _size = vectorToMove._size;
                    _data = vectorToMove._data;
                    vectorToMove._capacity = 0;
                    vectorToMove._size = 0;
                    vectorToMove._data = nullptr;
                }

                ~Vector() { delete [] _data; }

                iterator & begin() const {
                    try {
                        return *(new iterator{_data}); 
                    }
                    catch(const std::exception &e) {
                        std::cout << "Standard excepton: " << e.what() << std::endl;
                    }
                }

                iterator & end() const {
                    try {
                        return *(new iterator{_data + _size});
                    }
                    catch(const std::exception &e) {
                        std::cout << "Standard excepton: " << e.what() << std::endl;
                    }
                }

                iterator & rbegin() const {
                    try {
                        return *(new iterator{_data + _size - 1});
                    }
                    catch(const std::exception &e) {
                        std::cout << "Standard excepton: " << e.what() << std::endl;
                    }
                }

                iterator & rend() const {
                    try {
                        return *(new iterator{_data - 1});
                    }
                    catch(const std::exception &e) {
                        std::cout << "Standard excepton: " << e.what() << std::endl;
                    }
                }

                void push_back(const T & value) {
                    if(!_size) {
                        _size = 1;
                        _capacity = 1;
                        try {
                            _data = new T[_size];
                        }
                        catch(const std::exception &e) {
                            std::cout << "Standard excepton: " << e.what() << std::endl;
                        }
                    }
                    else if(++_size > _capacity) {
                        _capacity = 1;
                        while(_capacity < _size) _capacity *= 2;
                        T * newData;
                        try {
                            newData = new T[_capacity];
                        }
                        catch(const std::exception &e) {
                            std::cout << "Standard excepton: " << e.what() << std::endl;
                        }
                        std::memcpy(newData, _data, _size*sizeof(T));
                        delete [] _data;
                        _data = newData;
                    }
                    std::memcpy(_data+_size-1, &value, sizeof(T));
                }

                T & at(const std::size_t index) {
                    assert(index < _size);
                    return _data[index];
                }
                    
                T & operator[](const std::size_t index) {
                    return _data[index];
                }

                T & front() {
                    return _data[0];
                }
                
                T & back() {
                    return _data[_size-1];
                }

                void resize(std::size_t size) { _size = size; }

                const std::size_t size() const { return _size; }

                const std::size_t capacity() const { return _capacity; }

            private:
                std::size_t _capacity;
                std::size_t _size;
                T * _data;

        };

}

#endif
