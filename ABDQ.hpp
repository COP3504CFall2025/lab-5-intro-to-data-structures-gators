#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : capacity_(4), size_(0), front_(0), back_(0) {
        data_ = new T[capacity_];
    }
    explicit ABDQ(std::size_t capacity) : capacity_(capacity), size_(0), front_(0), back_(0) {
        data_ = new T[capacity_];
    }
    ABDQ(const ABDQ& other) : capacity_(other.capacity_), size_(other.size_), front_(0), back_(other.size_) {
        data_ = new T[other.capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
        }
    }
    ABDQ(ABDQ&& other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_){
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;

        T* data_2 = new T[other.capacity_];
        for (std::size_t i = 0; i < other.size_; ++i) {
            data_2[i] = other.data_[(other.front_ + i) % other.capacity_];
        }
        delete[] data_;
        data_ = data_2;
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = 0;
        back_ = size_ % capacity_;

        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_  = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        
        return *this;
    }
    ~ABDQ() noexcept {
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            ensureCapacity();
        }
        front_ = (front_ + capacity_ - 1) % capacity_;
        data_[front_] = item;
        size_++;
    }
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            ensureCapacity();
        }
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
        // Thanks Intro to Data Structures pptx
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty Data Structure!");
        }
        T value = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        shrinkIfNeeded();
        return value;
    }
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty Data Structure!");
        }
        back_ = (back_ - 1 + capacity_) % capacity_;
        T value = data_[back_];
        size_--;
        shrinkIfNeeded();
        return value;
    }

    void ensureCapacity() {
        std::size_t new_capacity_;
        if (capacity_ != 0) {
            new_capacity_ = capacity_ * SCALE_FACTOR;
        } else {
            new_capacity_ = SCALE_FACTOR;
        }
        T* data_2 = new T[new_capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_2[i] = data_[(front_ + i) % capacity_];
        }
        delete[] data_;
        data_ = data_2;
        capacity_ = new_capacity_;
        front_ = 0;
        back_  = size_ % capacity_;
    }

    void shrinkIfNeeded() {
        if (capacity_ <= 1) return;
        if (size_ * SCALE_FACTOR > capacity_) return;
        std::size_t new_capacity_ = capacity_ / SCALE_FACTOR;
        if (new_capacity_ < 1) new_capacity_ = 1;
        T* data_2 = new T[new_capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_2[i] = data_[(front_ + i) % capacity_];
        }
        delete[] data_;
        data_ = data_2;
        capacity_ = new_capacity_;
        front_ = 0;
        back_  = size_ % capacity_;
    }

    void PrintForward() {
        if (size_ == 0) {
            throw std::runtime_error("Empty Data Structure!");
        }
        for (int i = 0; i < size_; i++) {
            std::cout << data_[i] << std::endl;
        }
    }

    void PrintReverse() {
        if (size_ == 0) {
            throw std::runtime_error("Empty Data Structure!");
        }
        for (int i = size_ - 1; i >= 0; i--) {
            std::cout << data_[i] << std::endl;
        }
    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw std::runtime_error("Empty Data Structure!");
        }
        return data_[front_];
    }
    const T& back() const override {
        if (size_ == 0) {
            throw std::runtime_error("Empty Data Structure!");
        }
        return data_[(back_ + capacity_ - 1) % capacity_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};
