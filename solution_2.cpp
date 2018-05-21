#include <string>
#include <iostream>

template <typename T>
class node {
	T value;
	node<T>* next;
public:
	node(T x, node<T>* nxt = nullptr) : value(x), next(nxt) {}
	T get_value() {
		return value;
	}

	node<T>* get_next() {
		return next;
	}

	void set_value(T x) {
		value = x;
	}

	void set_next(node<T>* nxt) {
		next = nxt;
	}

};

template <typename T>
node<T>* find_kth_to_last(node<T>* head, int k) {
	node<T>* tail = head;
	node<T>* kth = head;
	int count = 0;
	while (count < k) {
		if (tail->get_next() == nullptr) {
			return nullptr;
		}
		tail = tail->get_next();
		count++;
	}
	while (tail->get_next() != nullptr) {
		tail = tail->get_next();
		kth = kth->get_next();
	}
	return kth;
}

int main() {
	node<int>* head = new node<int>(0, new node<int>(1));
	node<std::string>* head_1 = new node<std::string>("Anna", new node<std::string>("Kopeliovich"));
	int k;
	std::cout << "Write k\n";
	std::cin >> k;
	node<int>* kth_1 = find_kth_to_last(head, k);
	node<std::string>* kth = find_kth_to_last(head_1, k);
	if (kth != nullptr) {
		std::cout << kth->get_value() << ' ' << kth_1->get_value();
	} else {
		std::cout << "List less, than k = " << k << "\n";
	}
	return 0;
}
