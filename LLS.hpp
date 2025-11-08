#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
        T var = list.getHead()->data;
        list.removeHead();
        return var;
    }

    // Access
    T peek() const override {
        if (list.getHead() == nullptr) {
            int placeholder = 0;
            return placeholder;
        }
        return list.getHead()->data;
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    void PrintForward() const {
		list.printForward();
	}
	void PrintReverse() const {
		list.printReverse();
	}
};