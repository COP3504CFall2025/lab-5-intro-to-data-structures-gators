#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ(){
        array_ = new T[1];
        capacity_ = 1;
        curr_size_ = 0;
    }
    explicit ABQ(const size_t capacity){
        array_ = new T[capacity];
        capacity_ = capacity;
        curr_size_ = 0;
    }
    ABQ(const ABQ& other){
        this->array_ = new T[other.capacity_];
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        for (int i = 0; i < other.curr_size_; i++){
            this->array_[i] = other.array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs){
        if (this == &rhs){
            return *this;
        }
        delete[] this->array_;
        this->array_ = new T[rhs.capacity_];
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        for (int i = 0; i < rhs.curr_size_; i++){
            this->array_[i] = rhs.array_[i];
        }
        return *this;
    }
    ABQ(ABQ&& other) noexcept{
        this->array_ = other.array_;
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }
    ABQ& operator=(ABQ&& rhs) noexcept{
        if (this == &rhs){
            return *this;
        }
        delete[] this->array_;
        this->array_ = rhs.array_;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        rhs.array_ = nullptr;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        return *this;
    }
    ~ABQ() noexcept {
        delete[] this->array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override { return curr_size_;}
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}
    [[nodiscard]] T* getData() const noexcept { return array_;}

    // Insertion
    void enqueue(const T& data) override{
        if (curr_size_ == capacity_){
            if (capacity_ == 0) {capacity_ = 1;}
            else { capacity_ *= scale_factor_;}
            T* temp = new T[capacity_];
            for (int i = 0; i < curr_size_; i++){
                temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
        }
        array_[curr_size_] = data;
        curr_size_ += 1;
    }

    // Access
    T peek() const override {
        if (curr_size_ > 0){ return array_[0];}
        throw std::runtime_error("ABQ is empty");
    };

    // Deletion
    T dequeue() override{
        if (curr_size_ == 0){
            throw std::runtime_error("ABQ is empty");
        }
        T value = array_[0];
        for (int i = 0; i < curr_size_-1; i++){
            array_[i] = array_[i+1];
        }
        curr_size_ -= 1;

        if (curr_size_ > 1 && curr_size_ < capacity_ / scale_factor_) {
            capacity_ /= scale_factor_;
            T* temp = new T[capacity_];
            for (int i = 0; i < curr_size_; i++){
                temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
        }

        return value;
    }

};
