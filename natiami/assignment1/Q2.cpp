#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <algorithm>
#include <array> 

using namespace std;

template<typename T>
class List{
public:
	T key;
	List<T>* next;

	List(T k){ key = k; }
};

template<typename T>
List<T>* findKthElement(List<T>* list, int k){
	List<T>* kth = list;
	for (size_t i = 0; i < k; i++)
	{
		list = list->next;
	}
	while (list->next != NULL){
		list = list->next;
		kth = kth->next;
	}
	return kth;
}

int main(){

	int k;

	List<int>* head = new List < int >(20);
	List<int>* list = head;
	// Create single linked list
	for (size_t i = 1; i <= 20; i++)
	{
		list->next = new List < int >(20 - i);
		list = list->next;
	}

	// Print out the list
	list = head;
	cout << "The list is: ";
	while (list != NULL){
		cout << list->key << " ";
		list = list->next;
	}
	cout << endl;

	cout << "Input k value netween 0 and 20" << endl;
	cin >> k;

	cout << findKthElement(head, k)->key << endl;

	return 0;
}