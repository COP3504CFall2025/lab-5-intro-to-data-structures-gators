#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() : list(LinkedList<T>()) {};

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    };

    // Deletion
    T dequeue() override {
        list.removeHead();
    };

    // Access
    T peek() const override {
        list.getTail();
    };

    // Getter
    std::size_t getSize() const noexcept override {
        list.getCount();
    };
};