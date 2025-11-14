#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
public:

	struct Node {
		T data;
		Node* prev;
		Node* next;
	};

	// Behaviors
	void printForward() const{
		if (count == 0){
			std::cout << "Empty Linked List" << std::endl;
			return;
		}
		Node* copy = head;
		while (copy) {
			std::cout << (copy->data) << std::endl;
			copy = copy->next;
		}
	}
	void printReverse() const{
		if (count == 0){
			std::cout << "Empty Linked List" << std::endl;
			return;
		}
		Node* copy = tail;
		while (copy) {
			std::cout << (copy->data) << std::endl;
			copy = copy->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return count;}
	Node* getHead(){return head;}
	const Node* getHead() const {return head;}
	Node* getTail() {return tail;}
	const Node* getTail() const {return tail;}

	// Insertion
	void addHead(const T& data){
		if (count != 0){
			Node* newHead = new Node({data, nullptr, head});
			head->prev = newHead;
			head = newHead;
		} else {
			head = new Node({data, nullptr, nullptr});
			tail = head;
		}
		count++;
	}
	void addTail(const T& data){
		if (count != 0){
			Node* newTail = new Node({data, tail, nullptr});
			tail->next = newTail;
			tail = newTail;
		} else {
			head = new Node({data, nullptr, nullptr});
			tail = head;
		}
		count++;
	}

	// Removal
	bool removeHead(){
		if (count == 0){
			return false;
		} 
		Node* prevHead = head;
		if (count == 1){
			head = nullptr;
			tail = nullptr;
		} else {
			head = head->next;
			head->prev = nullptr;
		}
		delete prevHead;
		count--;
		return true;
	}
	bool removeTail(){
		if (count == 0){
			return false;
		} 
		Node* prevTail = tail;
		if (count == 1){
			head = nullptr;
			tail = nullptr;
		} else {
			tail = tail->prev;
			tail->next = nullptr;
		}
		delete prevTail;
		count--;
		return true;
	}
	void clear(){
		while (removeHead()){}
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
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
	}

	LinkedList<T>& operator=(const LinkedList<T>& rhs){
		if (this == &rhs){
			return *this;
		}
		clear();
		Node* copy = rhs.head;
		while (copy) {
			addTail(copy->data);
			copy = copy->next;
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList(){
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list){
		head = nullptr;
		tail = nullptr;
		count = 0;
		Node* copy = list.head;
		while (copy) {
			addTail(copy->data);
			copy = copy->next;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept{
		this->head = other.head;
		this->tail = other.tail;
		this->count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList(){
		clear();
	}

private:
	// Stores pointers to first and last nodes and count

	Node* head;
	Node* tail;
	unsigned int count;

};


