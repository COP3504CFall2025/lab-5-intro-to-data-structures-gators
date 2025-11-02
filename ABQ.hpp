#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{
private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() : array_(new T[1]), capacity_(1), curr_size_(0) {};
    explicit ABQ(const size_t capacity) {
        this->array_ = new T[capacity];
        this->capacity_ = capacity;
        this->curr_size_ = capacity;
    };
    ABQ(const ABQ& other) {
        this->array_ = new T[other.capacity_];
        this->curr_size_ = other.curr_size_;
        this->capacity_ = other.capacity_;

        for (size_t i = 0; i < other.capacity(); i++) {
            this->array_[i] = other.array_[i];
        }
    };
    ABQ& operator=(const ABQ& rhs) {
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
    ABQ(ABQ&& other) noexcept {
        this->array_ = other.array_;
        this->curr_size_ = other.curr_size_;
        this->capacity_ = other.capacity_;

        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
    };
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) {return *this;}

        delete[] this->array_;

        this->array_ = new T[rhs.capacity_];
        this->curr_size_ = rhs.curr_size_;
        this->capacity_ = rhs.capacity_;

        for (size_t i = 0; i < rhs.capacity_; i++) {
            this->array_[i] = rhs.array_[i];
        }

        return *this;
    };
    ~ABQ() noexcept {
        delete[] array_;
        array_ = nullptr;
        curr_size_ = 0;
        capacity_ = 0;
    };

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;};
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;};
    [[nodiscard]] T* getData() const noexcept {return *array_;};

    // Insertion
    void enqueue(const T& data) override {
        if (capacity_ == curr_size_) {
            if (capacity_ == 0) {
                capacity_ = 1;
            } else {
                capacity_ *= scale_factor_;
            }

            T* newData = new T[capacity_];
            for (size_t i = 0; i < capacity_ / scale_factor_; i++) {
                newData[i] = std::move(array_[i]);
            }
            
            delete[] array_;
            array_ = std::move(newData);
        }
        array_[curr_size_] = data;
        curr_size_++;
    };

    // Access
    T peek() const override {
        if (curr_size_ != 0) {
            throw std::runtime_error("Array-based queue is empty.");
        } else {
            return (capacity_-1)-curr_size_;
        }
    };

    // Deletion
    T dequeue() override {
        if (curr_size_ != 0) {
            T formerVal = peek();
            curr_size_--;
            if (curr_size_ < capacity_ / scale_factor_) {
                capacity_ /= scale_factor_;
                T* newData = new T[capacity_];
                for (size_t i = 0; i < capacity_; i++) {
                    newData[(capacity_-1)-i] = std::move(array_[(capacity_*scale_factor_-1)-i]);
                }
                delete[] array_;
                array_ = std::move(newData);
            }
            return formerVal;
        } else {
            throw std::runtime_error("Array-based queue is empty.");
        }
    };

};
