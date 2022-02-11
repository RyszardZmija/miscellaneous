#ifndef ITERATOR_H
#define ITERATOR_H

#include "Node.h"
#include <string>
#include <stdexcept>

template <typename T>
class Iterator {
public:
	explicit Iterator(Node<T> *curr) :
		curr(curr) {}

	T& operator*() const;

	// no decrement, we can't go back in a singly linked list
	// see doubly linked list for further reading
	// 
	// overloaded prefix version
	Iterator &operator++();

	// overloaded postfix version
	// return copy of the unincremented value
	Iterator operator++(int);

	// conversion is not implicitly applied by the compiler (except for
	// the condition context, loop or if condition etc.) and we need to use
	// static_cast<> to apply it
	explicit operator bool() const { return curr != nullptr; }
private:
	Node<T> *curr;

	void check(const std::string &msg) const {
		if (!curr) {
			throw std::out_of_range(msg);
		}
		
	}
};

template <typename T>
inline T &Iterator<T>::operator*() const {
	check("dereferenced iterator pointing to null");
	return (*curr).data;
}

template <typename T>
Iterator<T> &Iterator<T>::operator++() {
	check("increment past end");
	curr = curr->next;

	return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int) {
	check("increment past end");
	Iterator<T> temp(*this);
	++ *this;

	return temp;
}
#endif