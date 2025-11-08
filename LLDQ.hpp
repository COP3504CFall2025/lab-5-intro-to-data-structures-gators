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
        T var = list.getHead()->data;
        list.removeHead();
        return var;
    }
    T popBack() override {
        T var = list.getTail()->data;
        list.removeTail();
        return var;
    }

    // Element Accessors
    const T& front() const override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("Empty Data Structure!")
        }
        return list.getHead()->data;
    }
    const T& back() const override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("Empty Data Structure!")
        }
        return list.getTail()->data;
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






