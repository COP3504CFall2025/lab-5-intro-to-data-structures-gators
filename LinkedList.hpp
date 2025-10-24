#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return count;};
	Node* getHead() {return head;};
	const Node* getHead() const {return head;};
	Node* getTail()  {return tail;};
	const Node* getTail() const {return tail;};

	// Insertion
	void addHead(const T& data) {
		if (count == 0) {
			Node* headNode = new Node({data, nullptr, nullptr});
		} else {
			Node* headNode = new Node({data, nullptr, head});
		}
		head = headNode;
	};
	void addTail(const T& data) {
		if (count == 0) {
			Node* tailNode = new Node({data, nullptr, nullptr});
		} else {
			Node* tailNode = new Node({data, tail, nullptr});
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
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction/Destruction
	LinkedList() {
		
	};
	LinkedList(const LinkedList<T>& list) {
		head = new list.head;
		Node* aNode = list.head;
		if (aNode) {
			count++;
		}
		while (aNode->next) {
			addTail(aNode->next->data);
			count += 1;
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


