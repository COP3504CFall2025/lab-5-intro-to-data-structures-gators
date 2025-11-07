#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
		Node<T>* ptr = head;
		while (ptr != nullptr) {
			std::cout << ptr->data << std::endl;
			ptr = ptr->next;
		}
	}
	void printReverse() const {
		Node<T>* ptr = tail;
		while (ptr != nullptr) {
			std::cout << ptr->data << std::endl;
			ptr = ptr->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node<T>* getHead() {
		return head;
	}
	const Node<T>* getHead() const {
		return head;
	}
	Node<T>* getTail() {
		return tail;
	}
	const Node<T>* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		Node<T>* new_node = new Node<T>{data, nullptr, head};
		if (head == nullptr) {
			head = std::move(new_node);
			tail = head;
		} else {
			new_node->next = head;
			head->prev = new_node;
			head = std::move(new_node);
		}
		count++;
	}
	void addTail(const T& data) {
		Node<T>* new_node = new Node<T>{data, tail, nullptr};
		if (tail == nullptr) {
			tail = std::move(new_node);
			head = tail;
		} else {
			new_node->prev = tail;
			tail->next = new_node;
			tail = std::move(new_node);
		}
		count++;
	}

	// Removal
	bool removeHead() {
		if (head == nullptr) {
			return false;
		}
		if (head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		}
		Node<T>* next_head = head->next;
		delete head;
		head = std::move(next_head);
		head->prev = nullptr;
		count--;
		return true;
	}
	bool removeTail() {
		if (tail == nullptr) {
			return false;
		}
		if (head == tail) {
			delete tail;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		}
		Node<T>* next_tail = tail->prev;
		delete tail;
		tail = std::move(next_tail);
		tail->next = nullptr;
		count--;
		return true;
	}
	void Clear() {
		bool val = true;
		while (val) {
			val = this->removeHead();
		}
	}
	void clear() {
		this->Clear();
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) return *this;
        this->Clear();

        head = std::move(other.head);
		other.head = nullptr;
		tail = std::move(other.tail);
		other.tail = nullptr;
		count = other.count;
		other.count = 0;

        return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) return *this;
        this->Clear();
		Node<T>* ptr = rhs.head;
		this->addHead(ptr->data);
		while (ptr->next != nullptr) {
			ptr = ptr->next;
			Node<T>* new_node = new Node{ptr->data, ptr->prev, ptr->next};
			head->next = new_node;
			tail = new_node;
		}
		count = rhs.count;

        return *this;
	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}
	LinkedList(const LinkedList<T>& list) {
		count = 0;
		head = nullptr;
		tail = nullptr;
		Node<T>* otherptr = list.head;
		while (otherptr != nullptr) {
			this->addTail(otherptr->data);
			otherptr = otherptr->next;
		}
		count = list.count;
	}
	LinkedList(LinkedList<T>&& other) noexcept {
        head = std::move(other.head);
		other.head = nullptr;
		tail = std::move(other.tail);
		other.tail = nullptr;
		count = other.count;
		other.count = 0;
	}
	~LinkedList() {
		this->Clear();
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};


