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
    LLQ() = default;

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override {
        T head = list.getHead()->data;
        list.removeHead();
        return head;
    }

    // Access
    T peek() const override {
        if (list.getHead() == nullptr) {
            return 0
        }
        return list.getHead()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    void PrintForward() {
        list.printForward();
    }
    void PrintReverse() {
        list.printReverse();
    }
};