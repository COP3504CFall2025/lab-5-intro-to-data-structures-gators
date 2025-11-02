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
        T datum = peek();
        list.removeHead();
        return datum;
    };

    // Access
    T peek() const override {
        if (list.getCount()) {
            return list.getHead()->data;
        } else {
            throw std::runtime_error("List-based queue is empty.");
        }
    };

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    };
};