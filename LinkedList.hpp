#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
	// Behaviors
	void PrintForward() const {
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
	void PrintReverse() const {
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
	void AddHead(const T& data) {
		Node* headNode;
		if (count == 0) {
			headNode = new Node({data, nullptr, nullptr});
			tail = headNode;
		} else {
			headNode = new Node({data, nullptr, this->head});
			head->prev = headNode;

		}
		head = headNode;
		count++;
	};
	void AddTail(const T& data) {
		Node* tailNode;
		if (count == 0) {
			tailNode = new Node({data, nullptr, nullptr});
			head = tailNode;
		} else {
			tailNode = new Node({data, this->tail, nullptr});
			tail->next = tailNode;
		}
		tail = tailNode;
		count++;
	}

	// Removal
	bool RemoveHead() {
		if (count > 1) {
			Node* newHead = head->next;
			delete head;
			head = newHead;
			count--;
			return true;
		}
		if (count == 1) {
			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		}
		return false;
	};
	bool RemoveTail() {
		if (count > 1) {
			Node* newTail = tail->prev;
			delete tail;
			tail = newTail;
			count--;
			return true;
		}
		if (count == 1) {
			delete tail;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		}
		return false;
	};
	void Clear() {
		while (RemoveHead()) {}
	};

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (*this == other) {
			return *this;
		}
		Clear();
		
		this->head = other.head;
		this->tail = other.tail;
		this->count = other.count;
		other.Clear();
	};
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (*this == other) {
			return *this;
		}
		Clear();

		Node* iNode;
		if (iNode) {
			addHead(list.head->data);
			count++;
		}
		while (iNode->next) {
			addTail(aNode->next->data);
			count++;
			iNode = aNode->next;
		}
	};

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {};

	LinkedList(const LinkedList<T>& list) {
		Node* iNode;
		if (iNode) {
			addHead(list.head->data);
			count++;
		}
		while (iNode->next) {
			addTail(aNode->next->data);
			count++;
			iNode = aNode->next;
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


