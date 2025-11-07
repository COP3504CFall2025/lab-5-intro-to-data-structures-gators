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
        ist.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        return list.removeHead();
    }
    T popBack() override {
        return list.removeTail();
    }

    // Element Accessors
    const T& front() const override {
        return list.getHead();
    }
    const T& back() const override {
        return list.getTail();
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






