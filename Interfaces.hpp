#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
    virtual void push(const T& item);
    virtual T pop();
    virtual T peek() const;
    virtual std::size_t getSize() const noexcept;
};


template <typename T>
class QueueInterface {
    virtual void enqueue(const T& item);
    virtual T dequeue();
    virtual T peek() const;
    virtual std::size_t getSize() const noexcept;
};


template <typename T>
class DequeInterface {
    virtual void pushFront(const T& item);
    virtual void pushBack(const T& item);
    virtual T popFront() override;
    virtual T popBack() override;
    virtual const T& front() const;
    virtual const T& back() const;
    virtual std::size_t getSize() const noexcept;
};

