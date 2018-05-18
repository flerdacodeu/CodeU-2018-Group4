#include <iostream>

using namespace std;

/**
    the expected node structure of the linked list.
*/
// template <typename T>
// struct Node{
//     Node* next;
//     T val;
// };


/**
    Get the kth last element of a singly linked list
    @param head - pointer to the first node of the kinked list
    @param k - the desired element. values from the range 1 to
            the n where n is the size of the linked list.
    @return pointer to the kth last node in the linked list if k
            is whithin the range, NULL otherwise.
    
    example:
    linked list = 1 -> 2 -> 3 -> 4 -> 5
    k = 2
    ------------------
    4
*/
template <typename T>
Node<T>* get_kth_last_element(Node<T>* head, int k){
    if (k < 1) return NULL; // k out of bounds
    // count num of elements in the linked list.
    Node<T>* curr_node = head;
    int size = 0;
    while (curr_node != NULL){
        ++size;
        curr_node = curr_node->next;
    }
    if (k > size) return NULL; // k out of bounds
    // get kth last node
    curr_node = head;
    int curr_pos = size;
    while (curr_pos > k){
        curr_node = curr_node->next;
        --curr_pos;
    }
    return curr_node;
}
