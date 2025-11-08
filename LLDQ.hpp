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
        T head = list.getHead()->data;
        list.removeHead();
        return head;
    }
    T popBack() override {
        T tail = list.getTail()->data;
        list.removeTail();
        return tail;
    }

    // Element Accessors
    const T& front() const override {
        Node<T>* var = list.getHead();
        if (var->data == nullptr) {
            return 0;
        }
        return var->data;
    }
    const T& back() const override {
        Node<T>* var = list.getTail()->data;
        if (var->data == nullptr) {
            return 0;
        }
        return var->data;
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






