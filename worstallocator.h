#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <cassert>


template<typename T, size_t N>
struct worst_allocator {
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    template<typename U, size_t M = N>
    struct rebind {
        using other = worst_allocator<U, M>;
    };

    worst_allocator() : cur_size(0) {
//        auto mem_buf = new T[size];
        auto mem_buf = std::malloc(N * sizeof(T));
        if (!mem_buf) {
            std::__throw_bad_alloc();
        }
        data_ = reinterpret_cast<T *>(mem_buf);
    };

    ~worst_allocator() = default;

    worst_allocator(const worst_allocator &other) : data_(other.data_), cur_size(other.cur_size) {

    }

    T *allocate(std::size_t n) {
        if (cur_size + n > max_size) {
            std::__throw_bad_alloc();
        }
        auto cur_data = &data_[cur_size];
        cur_size += n;
        if (!cur_data) {
            throw std::bad_alloc();
        }
        return reinterpret_cast<T *>(cur_data);
    }

    void deallocate(T *p, std::size_t n) {
        (void) p;
        cur_size -= n;
        if (cur_size == 0) {
            std::free(data_);
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    };

    template<typename U>
    void destroy(U *p) {
        p->~U();
    }

private:
    T *data_;
    size_t cur_size;
    size_t max_size = N;
};
