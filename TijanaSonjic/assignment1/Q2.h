#pragma once


template <class T>
class List{
private:
	template <class T>
	class Element {
	public:
		T info;
		Element* next;
	
		Element(T info, Element* next = nullptr) {
			this->info = info;
			this->next = next;
		}
	};
	Element<T>* head;
	Element<T>* tail;
	int count;
public:
	List() : head(nullptr), tail(nullptr), count(0){}

	~List();

	void addElement(T info);

	Element<T>* getKthToLastElement(int position);

	void printValueOfKthKthToLastElement(int position);

	void printList();
};


template <typename T>
void List<T>::addElement(T info) {
	if (!head) {
		head = tail = new Element<T>(info);
	}
	else {
		tail->next = new Element<T>(info);
		tail = tail->next;
	}
	count++;
}

template <class T>
List<T>::Element<T>* List<T>::getKthToLastElement(int position) {
	if (position < 0 || position >= count)
		return nullptr;

	// Make a distance between these two pointers for position elements
	Element<T>* firstPointer = head;
	Element<T>* secondPointer = head;
	while (position >= 0) {
		firstPointer = firstPointer->next;
		position--;
	}

	// Move both pointers
	while (firstPointer) {
		firstPointer = firstPointer->next;
		secondPointer = secondPointer->next;
	}

	return secondPointer;
}

template <class T>
void List<T>::printValueOfKthKthToLastElement(int position) {
	Element<T>* element = getKthToLastElement(position);
	if (element)
		cout << element->info << endl;
	else
		cout << "Error" << endl;
}

template <class T>
void List<T>::printList() {
	for (Element<T>* temp = head; temp; temp = temp->next)
		cout << temp->info << " ";
	cout << endl;
}

template <class T>
List<T>::~List() {
	Element<T>* temp = nullptr;
	while (head) {
		temp = head;
		head = head->next;
		temp->next = nullptr;
		delete temp;
	}
	head = nullptr;
	count = 0;
}
