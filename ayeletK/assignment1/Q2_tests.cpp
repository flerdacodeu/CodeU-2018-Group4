/*  all tests methods return true when the test passes, false if fails */

// ---------- setup ----------
// create list of integers with values from 1 up to size
Node<int>* create_integer_list(int size){
  if (size < 1) return NULL;
  Node<int>* head = NULL;
  Node<int>* curr_node = head;
  Node<int>* new_node;
  for (int i = 1; i <= size; ++i){
    new_node = new Node<int>();
    new_node->val = i;
    new_node->next = NULL;
    if (i == 1){
      head = new_node;
      curr_node = new_node;
    }
    curr_node->next = new_node;
    curr_node = curr_node->next;
  }
  return head;
}

void delete_integer_list(Node<int>* head){
  Node<int>* node_to_delete;
  while (head != NULL){
    node_to_delete = head;
    head = head->next;
    node_to_delete->next = NULL;
    delete(node_to_delete);
  }
}

// ---------- Test get_list_size ----------
bool test_get_list_size_of_empty_list(){
  Node<int>* head = NULL;
  return get_list_size(head) == 0;
}

bool test_get_list_size_of_non_empty_list(int expected_size){
  Node<int>* head = create_integer_list(expected_size);
  int size = get_list_size(head);
  delete_integer_list(head);
  return size == expected_size;
}

bool test_get_list_size(){
  int expected_size = 3;
  return test_get_list_size_of_empty_list() && test_get_list_size_of_non_empty_list(expected_size);
}

// ---------- Test get_kth_last_element ----------
bool test_k_out_of_range(Node<int>* head, int test_size){
  Node<int>* res1 = get_kth_last_element(head, -1); // correct k is in the range [1,test_size]
  Node<int>* res2 = get_kth_last_element(head, test_size + 1);
  return res1 == NULL && res2 == NULL; // for k that is out of range, the method is expected to return NULL
}

bool test_k_in_range(Node<int>* head, vector<int> reversed_list_values){
  int size = reversed_list_values.size();
  Node<int>* kth_last_result;
  for (int i = 1; i <= size; ++i){
    kth_last_result = get_kth_last_element(head, i);
    if (kth_last_result == NULL) return false;
    else if (kth_last_result->val != reversed_list_values[i-1]) // vector indexes start at 0
      return false;
  }
  return true;
}

bool test_get_kth_last_element(){
  int test_size = 5;  // test a list with 5 integers 1->2->3->4->5
  vector<int> reversed_list_values = {5,4,3,2,1};
  Node<int>* head = create_integer_list(test_size);
  bool k_out_of_range = test_k_out_of_range(head, test_size);
  bool k_in_range = test_k_in_range(head, reversed_list_values);
  delete_integer_list(head);
  return k_out_of_range && k_in_range;
}
