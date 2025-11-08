#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() = default;

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        list.removeHead();
        return list.getHead()->data;
    }
    T popBack() override {
        list.removeTail();
        return list.getTail()->data;
    }

    // Element Accessors
    const T& front() const override {
        if (list.getHead() == nullptr) {
            return 0;
        }
        return list.getHead()->data;
    }
    const T& back() const override {
        if (list.getHead() == nullptr) {
            return 0;
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






