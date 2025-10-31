#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() : list(LinkedList<T>()) {};

    // Insertion
    void push(const T& item) override {
        list.AddTail(item);
    };

    // Deletion
    T pop() override {
        list.RemoveTail();
    };

    // Access
    T peek() const override {
        list.getTail();
    };

    //Getters
    std::size_t getSize() const noexcept override {
        list.getCount();
    };
};