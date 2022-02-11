#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
	Node(const T &data, Node *next) :
		data(data), next(next) {}
	Node() = default;

	T data;
	Node *next = nullptr;
};

template <typename T>
bool operator==(const Node<T> &lhs, const Node<T> &rhs) {
	return lhs.data == rhs.data &&
		lhs.next == rhs.next;
}

template <typename T>
bool operator!=(const Node<T> &lhs, const Node<T> &rhs) {
	return !(lhs == rhs);
}
#endif