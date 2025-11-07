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
		head = std::move(new_node);
		count++;
	}
	void addTail(const T& data) {
		Node<T>* new_node = new Node<T>{data, tail, nullptr};
		tail->next = new_node;
		tail = std::move(new_node);
		count++;
	}

	// Removal
	bool removeHead() {
		Node<T>* next_head = head->next;
		delete head;
		head = std::move(next_head);
		count--;
		return true;
	}
	bool removeTail() {
		Node<T>* next_tail = tail->prev;
		delete tail;
		tail = std::move(next_tail);
		count--;
		return true;
	}
	void Clear() {
		Node<T>* ptr = head;
		while (ptr != nullptr) {
			Node<T>* ptr_next = ptr->next;
			delete ptr;
			ptr = std::move(ptr_next);
		}
		count = 0;
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
		while (ptr != nullptr) {
			ptr = ptr->next;
			Node<T>* new_node = new Node(ptr->data, ptr->prev, ptr->next);
			head->next = new_node;
			tail = new_node;
		}
		count = rhs.count;

        return *this;
	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}
	LinkedList(const LinkedList<T>& list) {
		this->Clear();
		Node<T>* ptr = list.head;
		this->addHead(ptr->data);
		while (ptr != nullptr) {
			ptr = ptr->next;
			Node<T>* new_node = new Node(ptr->data, ptr->prev, ptr->next);
			head->next = new_node;
			tail = new_node;
		}
		count = list.count;
	}
	LinkedList(LinkedList<T>&& other) noexcept {
		this->Clear();

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


