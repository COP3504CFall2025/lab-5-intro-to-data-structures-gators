#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
		if (!count) {
			cout << "No elements.";
		}

		Node* printNode = head;
		cout << printNode.data;
		while (printNode->next) {
			cout << printNode.data << endl;
			printNode = printNode->next;
		}
	};
	void printReverse() const {
		if (!count) {
			cout << "No elements.";
		}

		Node* printNode = tail;
		cout << printNode.data;
		while (printNode->prev) {
			cout << printNode.data << endl;
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
		} else {
			headNode = new Node({data, nullptr, this->head});
			head->prev = headNode;

		}
		head = headNode;
	};
	void addTail(const T& data) {
		Node* tailNode;
		if (count == 0) {
			tailNode = new Node({data, nullptr, nullptr});
		} else {
			tailNode = new Node({data, this->tail, nullptr});
			tail->next = tailNode;
		}
		tail = tailNode;
	}

	// Removal
	bool removeHead() {
		if (count > 1) {
			Node* newHead = head->next;
			delete head;
			head = newHead;
		}
		if (count == 1) {
			delete head;
			head = nullptr;
			tail = nullptr;
		}
	};
	bool removeTail() {
		if (count > 1) {
			Node* newTail = tail->prev;
			delete tail;
			tail = newTail;
		}
		if (count == 1) {
			delete tail;
			head = nullptr;
			tail = nullptr;
		}
	};
	void Clear() {
		while (head) {
			removeHead();
		}
	};

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {

	};
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {

	};

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {};

	LinkedList(const LinkedList<T>& list) {
		head = new list.head;
		Node* aNode = list.head;
		if (aNode) {
			count++;
		}
		while (aNode->next) {
			addTail(aNode->next->data);
			count ++;
		}
	};
	LinkedList(LinkedList<T>&& other) noexcept {
		this->head = other.head;
		this->tail = other.tail;
		this->count = other.count;
		other.Clear();

	};
	~LinkedList() {
		Clear();
	};

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
};


