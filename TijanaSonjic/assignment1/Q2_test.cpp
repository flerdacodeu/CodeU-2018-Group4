#include "List.h"
#include <iostream>

using namespace std;


int main() {
	int numberOfElements = 10;
	int k = 0;
	List<int> *list = new List<int>();

	for (int i = 0; i < numberOfElements; i++)
		list->addElement(10*i);

	list->printList();

	while (true) {
		cout << "k=";
		cin >> k;
		cout << "Value of Kth to last element: (k=" << k << ")" << endl;
		list->printValueOfKthKthToLastElement(k);
	}
	system("PAUSE");
	return 0;
}