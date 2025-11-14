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
    // Big 5
    ABDQ(){
        data_ = new T[4];
        capacity_ = 4;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }
    explicit ABDQ(std::size_t capacity){
        data_ = new T[capacity];
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }
    ABDQ(const ABDQ& other){
        this->data_ = new T[other.capacity_];
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = 0;
        this->back_ = other.size_;
        for (int i = 0; i < other.size_; i++){
            this->data_[i] = other.data_[(other.front_ + i) % other.capacity_];
        }
    }
    ABDQ(ABDQ&& other) noexcept{
        this->data_ = other.data_;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other){
        if (this == &other){
            return *this;
        }
        delete[] this->data_;
        this->data_ = new T[other.capacity_];
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = 0;
        this->back_ = other.size_;
        for (size_t i = 0; i < other.size_; i++) {
            this->data_[i] = other.data_[(other.front_ + i) % other.capacity_];
        }
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept{
        if (this == &other){
            return *this;
        }
        delete[] this->data_;
        this->data_ = other.data_;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }
    ~ABDQ(){
        delete[] this->data_;
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override{
        if (size_ == capacity_){
            std::size_t oldCapacity = capacity_;
            if (capacity_ == 0) {
                capacity_ = 1;
                data_ = new T[capacity_];
            }
            else { 
                capacity_ *= SCALE_FACTOR;
                T* temp = new T[capacity_];
                for (int i = 0; i < size_; i++){
                    temp[i] = data_[(front_ + i) % oldCapacity];
                }
                delete[] data_;
                data_ = temp;
                front_ = 0;
                back_ = size_;
            }
        }
        if (front_ == 0){
            front_ = capacity_ - 1;
        } else{
            front_ = front_-1;
        }
        data_[front_] = item;
        size_ += 1;
    }
    void pushBack(const T& item) override{
        if (size_ == capacity_){
            std::size_t oldCapacity = capacity_;
            if (capacity_ == 0) {
                capacity_ = 1;}
            else { capacity_ *= SCALE_FACTOR;}
            T* temp = new T[capacity_];
            for (int i = 0; i < size_; i++){
                temp[i] = data_[(front_ + i) % oldCapacity];
            }
            delete[] data_;
            data_ = temp;
            front_ = 0;
            back_ = 0;
        }
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_ += 1;
    }

    // Deletion
    T popFront() override{
        if (size_ == 0){
            throw std::runtime_error("ABDQ is empty");
        }
        T value = data_[front_];
        front_ = (front_+1) % capacity_;
        size_ -= 1;

        if (size_ > 0 && size_ < capacity_ / SCALE_FACTOR) {
            int oldCapacity = capacity_;
            capacity_ /= SCALE_FACTOR;
            
            T* temp = new T[capacity_];
            for (int i = 0; i < size_; i++){
                temp[i] = data_[(front_ + i) % oldCapacity];
            }
            
            delete[] data_;
            data_ = temp;
            front_ = 0;
            back_ = size_;
        }

        return value;
    }
    T popBack() override{
        if (size_ == 0){
            throw std::runtime_error("ABDQ is empty");
        }
        back_ = (back_ + capacity_ - 1) % capacity_;
        size_ -= 1;

        if (size_ > 0 && size_ < capacity_ / SCALE_FACTOR) {
            int oldCapacity = capacity_;
            capacity_ /= SCALE_FACTOR;
            
            T* temp = new T[capacity_];
            for (int i = 0; i < size_; i++){
                temp[i] = data_[(front_ + i) % oldCapacity];
            }
            
            delete[] data_;
            data_ = temp;
            front_ = 0;
            back_ = size_;
        }

        return data_[back_];
    }

    // Access
    const T& front() const override{
        if (size_ > 0){ return data_[front_];}
        throw std::runtime_error("ABDQ is empty");
    }
    const T& back() const override{
        if (size_ > 0){ return data_[(back_ + capacity_ - 1) % capacity_];}
        throw std::runtime_error("ABDQ is empty");
    }

    // Getters
    std::size_t getSize() const noexcept override { return size_;}

};
