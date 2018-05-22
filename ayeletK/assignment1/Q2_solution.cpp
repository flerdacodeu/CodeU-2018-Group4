#include <iostream>

using namespace std;

//the expected node structure of the linked list.
template <typename T>
struct Node{
  Node* next;
  T val;
};

int get_list_size(Node<T>* head){
  Node<T>* curr_node = head;
  int size = 0;
  while (curr_node != NULL){
    ++size;
    curr_node = curr_node->next;
  }
  return size;
}

// Get the kth last element of a singly linked list
template <typename T>
Node<T>* get_kth_last_element(Node<T>* head, int k){
  if (k < 1) return NULL; // k out of bounds
  int size = get_list_size(head);
  if (k > size) return NULL; // k out of bounds
  // get kth last node
  curr_node = head;
  int kth_last_position = size - k;;
  for (int i = 0; i < kth_last_position; ++i){
    curr_node = curr_node->next;
  }
  return curr_node;
}
