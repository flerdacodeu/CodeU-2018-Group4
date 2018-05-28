#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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
	if (list == NULL){
		cout << "List is empty"<<endl; 
		return NULL;
	}
	if (k < 0){
		cout << "Negative K values are not allowed"<<endl;
		return NULL;
	}

	List<T>* kth = list;
	for (size_t i = 0; i < k; i++)
	{
		if (list->next != NULL)
			list = list->next;
		else{
			cout << "K is too large" << endl;
			return NULL;
		}
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

	cout << "Input integer k value between 0 and 20" << endl;
	cin >> k;

	List<int>* head_empty = NULL; // empty list for check
	
	List<int>* kth_element = findKthElement(head, k);
	if (kth_element != NULL) cout << kth_element->key << endl;

	return 0;
}
