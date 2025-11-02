#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Big 5 + Parameterized Constructor
    ABS() : array_(new T[1]), capacity_(1), size_(0) {};
    explicit ABS(const size_t capacity) {
        this->array_ = new T[capacity];
        this->capacity_ = capacity;
        this->curr_size_ = capacity;
    };
    ABS(const ABS& other) {
        this->array_ = new T[other.capacity_];
        this->curr_size_ = other.curr_size_;
        this->capacity_ = other.capacity_;

        for (size_t i = 0; i < other.capacity(); i++) {
            this->array_[i] = other.array_[i];
        }
    };
    ABS& operator=(const ABS& rhs) {
        if (this == &rhs) {return *this;}

        delete[] this->array_;

        this->array_ = new T[other.capacity_];
        this->curr_size_ = other.curr_size_;
        this->capacity_ = other.capacity_;

        for (size_t i = 0; i < other.capacity_; i++) {
            this->array_[i] = other.array_[i];
        }

        return *this;
    };
    ABS(ABS&& other) noexcept {
        this->array_ = other.array_;
        this->curr_size_ = other.curr_size_;
        this->capacity_ = other.capacity_;

        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
    };
    ABS& operator=(ABS&& rhs) noexcept {
        if (this == &rhs) {return *this;}

        delete[] this->array_;

        this->array_ = new T[other.capacity_];
        this->curr_size_ = other.curr_size_;
        this->capacity_ = other.capacity_;

        for (size_t i = 0; i < other.capacity_; i++) {
            this->array_[i] = other.array_[i];
        }

        return *this;
    };
    ~ABS() noexcept {
        delete[] array_;
        array_ = nullptr;
        curr_size_ = 0;
        capacity_ = 0;
    };

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;};

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;};

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {return *array_;};

    // Push item onto the stack
    void push(const T& data) override {
        curr_size_++;
        if (capacity_ < curr_size_) {
            if (capacity_ == 0) {
                capacity_ = 1;
            } else {
                capacity_ *= scale_factor_;
                T* newData = new T[capacity_];
                for (size_t i = 0; i < capacity_ / scale_factor_; i++) {
                    newData[i] = std::move(array_[i]);
                }
                
                delete[] array_;
                array_ = std::move(newData);
            }
        }
        array_[curr_size_-1] = data;
    };

    T peek() const override {
        return array_[curr_size_-1];
    };

    T pop() override {
        if (curr_size_ != 0) {
            T formerVal = peek();
            curr_size_--;
            if (curr_size_ < capacity_ / scale_factor_) {
                capacity_ /= scale_factor_;
                T* newData = new T[capacity_];
                for (size_t i = 0; i < capacity_; i++) {
                    newData[i] = std::move(array_[i]);
                }
                delete[] array_;
                array_ = std::move(newData);
            }
            return formerVal;
        } else {
            throw std::runtime_error("Array-based stack is empty.");
        }
    };
};
