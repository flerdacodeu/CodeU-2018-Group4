#include "tree_node.cpp"
#include "my_exceptions.cpp"
#include <iostream>
#include <list>

using namespace std;

template <typename Key>
bool is_parent(Key key, Node<Key>* curr_node){
  bool left_son_has_key = 
    curr_node->has_left() && curr_node->left->get_key() == key;
  bool right_son_has_key = 
    curr_node->has_right() && curr_node->right->get_key() == key;    
  return left_son_has_key || right_son_has_key;
}

template <typename Key>
list<Key> get_path_to_root(Key key, Node<Key>* curr_node){
    list<Key> res;
    if (!curr_node) return res;
    if (curr_node->get_key() == key){
        res.push_back(curr_node->get_key());
        return res;
    }
    res = get_path_to_root(key, curr_node->left);
    if (res.empty()) res = get_all_ancestors(key, curr_node->right);
    if (!res.empty()){
        res.push_back(curr_node->get_key());
        return res;
    }
    return res; // if reached here, key not found in the tree rooted with curr node.
}

template <typename Key>
list<Key> get_all_ancestors(Key key, Node<Key>* root){
    list<Key> path_res = get_path_to_root(key, root);
    if (path_res.front() == key) path_res.pop_front();
    return path_res; // now represents all ancestors list from bottom to root
}

template <typename Key>
void print_all_ancestors(Key key, Node<Key>* root){
  if (!root) throw emptyTreeException();
  list<Key> ancestors_keys = get_all_ancestors(key, root);
  if (ancestors_keys.empty() && root->get_key() != key) throw keyNotExistsException();
  typename list<Key>::iterator it;
  for (it = ancestors_keys.begin(); it != ancestors_keys.end(); ++it){
      cout << *it << " ";
  }
  cout << endl;
}
