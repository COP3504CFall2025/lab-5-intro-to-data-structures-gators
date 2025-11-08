#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <iostream>

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() : capacity_(1), curr_size_(0) {
        array_ = new T[capacity_];
    }
    explicit ABS(const size_t capacity) : capacity_(capacity), curr_size_(0) {
        array_ = new T[capacity_];
    }
    ABS(const ABS& other) {
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        array_ = new T[other.capacity_];
        for (std::size_t i = 0; i < other.curr_size_; i++) {
            this->data_[i] = other.data_[i];
        }
    }
    ABS& operator=(const ABS& rhs) {
        if (this == &rhs) return *this;
        delete[] array_;

        curr_size_ = rhs.curr_size_;
        capacity_ = rhs.capacity_;
        array_ = new T[rhs.capacity_];
        for (std::size_t i = 0; i < rhs.curr_size_; i++) {
            this->data_[i] = rhs.data_[i];
        }
        return *this;
    }
    ABS(ABS&& other) noexcept {
        array_ = other.array_;
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
    }
    ABS& operator=(ABS&& rhs) noexcept {
        if (this == &rhs) return *this;
        delete[] array_;

        array_ = rhs.array_;
        curr_size_ = rhs.curr_size_;
        capacity_ = rhs.capacity_;

        rhs.array_ = nullptr;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;

        return *this;
    }
    ~ABS() noexcept {
        delete[] array_;
        curr_size_ = 0;
        capacity_ = 0;
        array_ = nullptr;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    void ensureCapacity() {
        capacity_ *= scale_factor_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if (capacity_ == 0) { capacity_ = 1; array_ = new T[capacity_]; }
        if (curr_size_ >= capacity_) {
            this->ensureCapacity();
            T* data_2 = new T[capacity_];
            for (std::size_t i = 0; i < curr_size_; i++) {
                data_2[i] = array_[i];
            }
            data_2[curr_size_] = data;
            curr_size_++;
            delete[] array_;
            array_ = data_2;
        } else {
            array_[curr_size_] = data;
            curr_size_++;
        }
    }

    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty Data Structure!");
        }
        return array_[curr_size_ - 1];
    }

    T pop() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("Empty Data Structure!");
        }
        T popped = array_[curr_size_ - 1];
        if (curr_size_ <= capacity_/scale_factor_) {
            capacity_ /= scale_factor_;
            T* data_2 = new T[capacity_];
            for (std::size_t i = 0; i < curr_size_; i++) {
                data_2[i] = array_[i];
            }
            delete[] array_;
            array_ = data_2;
        }
        array_[curr_size_ - 1] = 0;
        curr_size_--;
        return popped;
    }

    void PrintForward() {
        for (int i = 0; i < curr_size_; i++) {
            std::cout << array_[i] << std::endl;
        }
    }

    void PrintReverse() {
        for (int i = curr_size_ - 1; i >= 0; i--) {
            std::cout << array_[i] << std::endl;
        }
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
