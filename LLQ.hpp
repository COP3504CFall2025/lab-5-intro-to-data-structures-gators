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
        return list.removeHead();
    }

    // Access
    T peek() const override {
        return list.getHead();
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    void printForward() const {
		list.printForward();
	}
	void printReverse() const {
		list.printReverse();
	}
};