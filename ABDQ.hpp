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
    ABDQ(const ABDQ& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[other.capacity_];
        for (std::size_t i = 0; i < other.size_; i++) {
            this->data_[i] = other.data_[i];
        }
    }
    ABDQ(ABDQ&& other) noexcept {
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;
        delete[] data_;

        T* data = new T[other.capacity_];
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = data;

        for (std::size_t i = 0; i < other.size_; i++) {
            this->data_[i] = other.data_[i];
        }
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

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
        if (size_ == capacity_ - 1) {
            throw std::runtime_error("Full Data Structure!");
        }
        front_ = (front_ - 1 + capacity_) % capacity_;
        data_[front_] = item;
        size_ = size_ + 1;
    }
    void pushBack(const T& item) override {
        if (size_ == capacity_ - 1) {
            throw std::runtime_error("Full Data Structure!");
        }
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_ = size_ + 1;
        // Thanks Intro to Data Structures pptx
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty Data Structure!");
        }
        T value = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_ = size_ - 1;
        return value;
    }
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("Empty Data Structure!");
        }
        back_ = (back_ - 1 + capacity_) % capacity_;
        T value = data_[back_];
        size_ = size_ - 1;
        return value;
    }

    void ensureCapacity() {
        capacity_ *= SCALE_FACTOR;
    }

    void shrinkIfNeeded() {
        if (size_ <= capacity_/SCALE_FACTOR) {
            capacity_ /= SCALE_FACTOR;
            T* data_2 = new T[capacity_];
            for (std::size_t i = 0; i < size_; i++) {
                data_2[i] = data_[i];
            }
            data_ = std::move(data_2);
        }
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
        return front_;
    }
    const T& back() const override {
        if (size_ == 0) {
            throw std::runtime_error("Empty Data Structure!");
        }
        return back_;
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};
