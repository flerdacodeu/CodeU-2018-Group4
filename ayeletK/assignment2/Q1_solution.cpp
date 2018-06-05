#include "tree_node.cpp"
#include <iostream>
#include <list>

using namespace std;

template <typename Key>
bool is_direct_ancestor(Key key, Node<Key>* curr_node){
  bool left_son_has_key = 
    curr_node->has_left() && curr_node->left->get_key() == key;
  bool right_son_has_key = 
    curr_node->has_right() && curr_node->right->get_key() == key;    
  return left_son_has_key || right_son_has_key;
}

template <typename Key>
list<Key> get_all_ancestors(Key key, Node<Key>* curr_node){
  list<Key> res;
  // if the current node is null, leaf or has the given key, it's not ancestor
  if (!curr_node || !curr_node->get_key() == key || curr_node->is_leaf()) return res;
  if (is_direct_ancestor(key, curr_node)){
    res.push_back(curr_node->get_key());
    return res;
  }
  res = get_all_ancestors(key, curr_node->left);
  if (res.empty()) res = get_all_ancestors(key, curr_node->right);
  if (!res.empty()){
    res.push_back(curr_node->get_key());
    return res;
  }
  return res; // if reached here, key not found in the tree rooted with curr node.
}

template <typename Key>
void print_all_ancestors(Key key, Node<Key>* root){
  if (!root) throw "The given tree is empty.";
  list<Key> ancestors_keys = get_all_ancestors(key, root);
  if (ancestors_keys.empty() && root->get_key() != key) throw "The given key does not exists in the given tree.";
  typename list<Key>::iterator it;
  for (it = ancestors_keys.begin(); it != ancestors_keys.end(); ++it){
    cout << *it << " ";
  }
  cout << endl;
}
