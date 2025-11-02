#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
private:
	// Stores pointers to first and last nodes and count
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};

	Node* head;
	Node* tail;
	unsigned int count;
public:
	// Behaviors
	void printForward() const {
		if (!count) {
			cout << "No elements.";
		}

		Node* printNode = head;
		while (printNode) {
			cout << printNode->data << endl;
			printNode = printNode->next;
		}
	};
	void printReverse() const {
		if (!count) {
			cout << "No elements.";
		}

		Node* printNode = tail;
		while (printNode) {
			cout << printNode->data << endl;
			printNode = printNode->prev;
		}
	};

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return count;};
	Node* getHead() {return head;};
	const Node* getHead() const {return head;};
	Node* getTail()  {return tail;};
	const Node* getTail() const {return tail;};

	// Insertion
	void addHead(const T& data) {
		Node* headNode;
		if (count == 0) {
			headNode = new Node({data, nullptr, nullptr});
			tail = headNode;
		} else {
			headNode = new Node({data, nullptr, getHead()});
			head->prev = headNode;

		}
		head = headNode;
		count++;
	};
	void addTail(const T& data) {
		Node* tailNode;
		if (count == 0) {
			tailNode = new Node({data, nullptr, nullptr});
			head = tailNode;
		} else {
			tailNode = new Node({data, getTail(), nullptr});
			tail->next = tailNode;
		}
		tail = tailNode;
		count++;
	}

	// Removal
	bool removeHead() {
		if (count == 0) {
			return false;
		} else if (count == 1) {
			delete head;
			head = nullptr;
			tail = nullptr;
		} else {
			Node* newHead = head->next;
			delete head;
			head = newHead;
			head->prev = nullptr;
		}
		count--;
		return true;
	};
	bool removeTail() {
		if (count == 0) {
			return false;
		} else if (count == 1) {
			delete tail;
			head = nullptr;
			tail = nullptr;
		} else {
			Node* newTail = tail->prev;
			delete tail;
			tail = newTail;
			tail->next = nullptr;
		}
		count--;
		return true;
	};
	void clear() {
		while (removeHead()) {}
	};

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) {
			return *this;
		}
		clear();
		
		this->head = other.head;
		this->tail = other.tail;
		this->count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

		return *this;
	};
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}
		clear();

		Node* iNode = rhs.head;
		while (iNode) {
			addTail(iNode->data);
			iNode = iNode->next;
		}

		return *this;
	};

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {};

	LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(0) {
		Node* iNode = list.head;
		while (iNode) {
			addTail(iNode->data);
			iNode = iNode->next;
		}
	};
	LinkedList(LinkedList<T>&& other) noexcept {
		this->head = other.head;
		this->tail = other.tail;
		this->count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	};
	~LinkedList() {
		clear();
	};
};


