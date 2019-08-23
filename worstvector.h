#pragma once
#include <cstdlib>


template<typename T, typename _Alloc = std::allocator<T>>
class WorstVector {
public:
    using Alloc = typename _Alloc::template rebind<T>::other;

    WorstVector() {
        size_ = 0;
        capa_ = 10;
        data_ = allocator.allocate(capa_);
        end_ = data_;

    }

    explicit WorstVector(size_t size) {
        size_ = size;
        capa_ = 2 * size_;
//        data_ = new T[capa_];
data_ = allocator.allocate(capa_);
        end_ = data_ + size;
    }

    ~WorstVector() {
//        if (data_ != nullptr) {
//            delete[] data_;
//        }
allocator.deallocate(data_, capa_);
        capa_ = 0;
        size_ = 0;
    }

    T &operator[](size_t index) {
        return *(data_ + index);
    }

    T *begin() {
        return data_;
    }

    T *end() {
        return end_;
    }

    const T *begin() const {
        return data_;
    }

    const T *end() const {
        return end_;
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capa_;
    }

    void PushBack(const T &value);

private:
    T *data_;
    T *end_;
    size_t size_;
    size_t capa_;
    Alloc allocator;

};

template<typename T, typename Allocator>
void WorstVector<T, Allocator>::PushBack(const T &value) {
    if (Size() >= Capacity()) {
        if (capa_ != 0) {
            capa_ *= 2;
        } else capa_ = 2;
        T *ptr = allocator.allocate(capa_);
        for (size_t i = 0; i < size_; i++) {
            ptr[i] = data_[i];
        }
        allocator.deallocate(data_, capa_);
        data_ = ptr;
        data_[size_++] = value;
        end_ = data_ + size_;
    } else {
        data_[size_++] = value;
        end_ = data_ + size_;
    }
}