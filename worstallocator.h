#ifndef TEST_WORSTALLOCATOR_H
#define TEST_WORSTALLOCATOR_H

#endif //TEST_WORSTALLOCATOR_H 

#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#pragma once


template<typename T, size_t size>
struct worst_allocator {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = worst_allocator<U, size>;
    };

    worst_allocator() =default;
    ~worst_allocator() = default;

    template<typename U>
    worst_allocator(const worst_allocator<U, size>&) {

    }

    T* allocate(std::size_t n) {
        if(cur_size + n > max_size){
            std::__throw_bad_alloc();
        }
        auto p = std::malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) {
        std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    };

    void destroy(T *p) {
        p->~T();
    }
private:
    size_t cur_size = 0;
    size_t max_size=size;
}; 
 