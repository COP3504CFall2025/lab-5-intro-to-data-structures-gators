#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

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
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept {
        array_ = other.array_;
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
    }
    ABS& operator=(ABS&& rhs) noexcept {
        if (this == &other) return *this;
        delete[] array_;

        array_ = other.array_;
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;

        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;

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

    // Push item onto the stack
    void push(const T& data) override {
        if (capacity_ == 0) { capacity_ = 1; array_ = new T[capacity_]; }
        if (curr_size_ >= capacity_) {
            this->ensureCapacity();
            T* data_2 = new T[capacity_];
            for (std::size_t i = 0; i < curr_size_; i++) {
                data_2[i] = array_[i];
            }
            data_2[curr_size_] = item;
            curr_size_++;
            delete[] array_;
            array_ = data_2;
        } else {
            array_[curr_size_] = item;
            curr_size_++;
        }
    }

    T peek() const override {
        if (curr_size_ == 0) {
            throw std::out_of_range("Index out of range");
        }
        return array_[0];
    }

    T pop() override {
        if (curr_size_ == 0) {
            throw std::out_of_range("Index out of range");
        }
        T popped = array_[0];
        array_[size_ - 1] = 0;
        curr_size_--;
        return popped;
    }

    void PrintForward() {
        for (int i = 0; i < size_; i++) {
            std::cout << data_[i] << std::endl;
        }
    }

    void PrintReverse() {
        for (int i = size_ - 1; i >= 0; i--) {
            std::cout << data_[i] << std::endl;
        }
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
