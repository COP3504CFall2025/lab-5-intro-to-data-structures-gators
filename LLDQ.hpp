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
        list.addHead(item);
    };
    void pushBack(const T& item) override {
        list.addTail(item);
    };

    // Core Removal Operations
    T popFront() override {
        T datum = front();
        list.removeHead();
        return datum;
    };
    T popBack() override {
        T datum = back();
        list.removeTail();
        return datum;
    };

    // Element Accessors
    const T& front() const override {
        if (list.getCount()) {
            return list.getHead()->data;
        }
    };
    const T& back() const override {
        if (list.getCount()) {
            return list.getTail()->data;
        }
    };

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    };
};






