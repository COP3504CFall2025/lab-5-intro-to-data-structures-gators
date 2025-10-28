#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

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
    // big 5
    // note that most code is resused from iDynamArray
    ABDQ() : data_(new T[4]), capacity_(4), size_(0), front_(0), back_(0) {};
    explicit ABDQ(std::size_t capacity) {
        this->data_ = new T[capacity];
        this->capacity_ = capacity;
        this->size_ = capacity;
        this->front_ = 0;
        this->back_ = 0;
    };
    ABDQ(const ABDQ& other) {
        this->data_ = new T[other.capacity_];
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        for (size_t i = 0; i < other.capacity(); i++) {
            this->data_[i] = other[i];
        }
    };
    ABDQ(ABDQ&& other) noexcept {
        this->data_ = other.data_;
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    };
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {return *this;}

        delete[] this->data_;

        this->data_ = new T[other.capacity_];
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        for (size_t i = 0; i < other.capacity_; i++) {
            this->data_[i] = other[i];
        }

        return *this;
    };
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {return *this;}

        delete[] this->data_;

        this->data_ = other.data_;
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;

        return *this;
    };
    ~ABDQ() override {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        front_ = 0;
        back_ = 0;
    };

    // insertion
    void pushFront(const T& item) override {
        size_++;
        ensureCapacity();
        data_[front_] = item;
        front_--;
    };
    void pushBack(const T& item) override {
        size_++;
        ensureCapacity();
        data_[back_] = item;
        back_++;
    };

    // deletion
    T popFront() override {
        if (size_ != 0) {
            size_--;
            front_++;
            shrinkIfNeeded();
        } else {
            throw std::out_of_range("Array-based deque is empty.");
        }
    };
    T popBack() override {
        if (size_ != 0) {
            size_--;
            back_--;
            shrinkIfNeeded();
        } else {
            throw std::out_of_range("Array-based deque is empty.");
        }
    };

    // access
    const T& front() const override {
        return data_[front_];
    };
    const T& back() const override {
        return data_[back_-1];
    };

    // getters
    std::size_t getSize() const noexcept override {
        return size_;
    };

    // resizes to capacity_ * 2
    void ensureCapacity() {
        if (capacity_ < size_) {

            size_t frontDifferential = capacity_-front_;

            // makes the array capacity one if empty
            if (capacity_ == 0) {
                capacity_ = 1;
            } else {
                capacity_ *= SCALE_FACTOR;
            }

            // doubles capacity_ by adding space between the tail and head
            T* newData = new T[capacity_];
            for (size_t i = 0; i < back_; i++) {
                newData[i] = std::move(data_[i]);
            }
            for (size_t i = 0; i >= front_; i++) {
                newData[i-(capacity_-1)] = std::move(data_[i]);
            }

            front_ = capacity_-frontDifferential;

            delete[] data_;
            data_ = std::move(newData);
        }
    }

    // reduces to half when sparse
    void shrinkIfNeeded() {
        if (size_ < capacity_ / SCALE_FACTOR) {

            size_t frontDifferential = capacity_-front_;
            capacity_ /= 2;

            // halves capacity_ by removing space between the tail and head
            T* newData = new T[capacity_];
            for (size_t i = 0; i < back_; i++) {
                newData[i] = std::move(data_[i]);
            }
            for (size_t i = 0; i >= front_; i++) {
                newData[i-(capacity_-1)] = std::move(data_[i]);
            }

            front_ = capacity_-frontDifferential;

            delete[] data_;
            data_ = std::move(newData);
        }
    }
};
