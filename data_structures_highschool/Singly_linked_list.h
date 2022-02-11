#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include "Node.h"
#include "Iterator.h"

#include <cstddef>
#include <stdexcept>

template <typename T>
class Singly_linked_list {
public:
	using pos = std::size_t;
	using size_type = std::size_t;

	Singly_linked_list() = default;

	// linked list manipulation
	void push_back(const T &item);
	void push_front(const T &item);
	void insert(const T &item, pos index);
	void pop_front();
	void pop_back();
	void erase(pos index);

	size_type size() const { return l_size; }
	// return iterator, for now there is only an implementation
	// of a non const iterator but const iterator would work in
	// a similar way, except that we should overload this function
	// on const and return it from a const member function
	Iterator<T> begin() { return Iterator<T>(head); }

	// copy control members
	// we need to control what happens when we copy, copy assign and
	// delete objects of this type because this type allocates external
	// resources i.e. dynamic memory and to conform to RAII paradigm we
	// need to define the 3 copy control members (we omit move operations)
	Singly_linked_list(const Singly_linked_list<T> &lst) {
		// unfortunately since this template is not fully implemented and we have problems with const violation
		// we need to use const_cast which in this case is okay because we cast to non const an object
		// but it's not changed in this non const context (copy function)
		copy(const_cast<Singly_linked_list<T>&>(lst), *this);
	}

	Singly_linked_list &operator=(const Singly_linked_list<T> &lst) {
		// protected against self-assignment by first copying the argument
		// and then deleting memory
		Singly_linked_list<T> cpy(lst);
		clear(*this);
		copy(cpy, *this);
	}
	
	~Singly_linked_list() {
		clear(*this);
	}

private:
	Node<T> *head = nullptr;
	size_type l_size = 0;

	static void clear(Singly_linked_list<T> &lst) {
		Node<T> *curr = lst.head;
		Node<T> *tmp = lst.head->next;

		while (tmp) {
			delete curr;
			curr = tmp;
			tmp = tmp->next;
		}

		delete curr;
		lst.head = nullptr;
	}

	static void copy(Singly_linked_list<T> &src, Singly_linked_list<T> &dest) {
		clear(dest);

		for (Iterator<T> it = src.begin(); it; ++it) {
			dest.push_back(*it);
		}
	}
};

template <typename T>
void Singly_linked_list<T>::push_front(const T &item) {
	Node<T> *cur_ptr = new Node<T>(item, head);
	head = cur_ptr;

	++l_size;
}

template <typename T>
void Singly_linked_list<T>::push_back(const T &item) {
	if (!head) {
		head = new Node<T>(item, nullptr);
	}
	else {
		Node<T> *cur_elem = head;

		while (cur_elem->next != nullptr) {
			cur_elem = cur_elem->next;
		}

		cur_elem->next = new Node<T>(item, nullptr);
	}

	++l_size;
}

// add an element before the passed index
template <typename T>
void Singly_linked_list<T>::insert(const T &item, pos index) {
	if (index > l_size) {
		throw std::out_of_range("invalid index for the list");
	}

	if (index == 0) {
		push_front(item);
	}
	else if (index == l_size) {
		push_back(item);
	}
	else {
		Node<T> *curr = head;
		Node<T> *temp = nullptr;

		// we stop at the element right before the indexed one so we can easily change
		// links
		for (int i = 0; curr->next != nullptr && i < index - 1; ++i) {
			curr = curr->next;
		}

		temp = curr->next;
		curr->next = new Node<T>(item, temp);
	}
}

template <typename T>
void Singly_linked_list<T>::pop_front() {
	if (head) {
		Node<T> *temp = head->next;
		delete head;
		head = temp;
	}
}

template <typename T>
void Singly_linked_list<T>::pop_back() {
	if (head) {
		Node<T> *curr = head;

		while (curr->next->next != nullptr) {
			curr = curr->next;
		}

		delete curr->next;
		curr->next = nullptr;
	}
}

// remove an element at the passed index
template <typename T>
void Singly_linked_list<T>::erase(pos index) {
	if (index >= l_size) {
		throw std::out_of_range("out of range index for erasure");
	}

	if (index == 0) {
		pop_front();
	}
	else {
		Node<T> *curr = head;
		Node<T> *temp = nullptr;

		for (int i = 0; curr->next != nullptr && i < index - 1; ++i) {
			curr = curr->next;
		}

		temp = curr->next;
		curr->next = temp->next;
		delete temp;
	}
}
#endif