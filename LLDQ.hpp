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
    LLDQ() : list(LinkedList<T>()) {};

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.AddHead(item);
    };
    void pushBack(const T& item) override {
        list.AddTail(item);
    };

    // Core Removal Operations
    T popFront() override {
        list.RemoveHead();
    };
    T popBack() override {
        list.RemoveTail();
    };

    // Element Accessors
    const T& front() const override {
        list.getHead();
    };
    const T& back() const override {
        list.getTail();
    };

    // Getter
    std::size_t getSize() const noexcept override {
        list.getCount();
    };
};






