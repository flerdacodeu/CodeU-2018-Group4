#include "tree_node.cpp"
#include <string>

using namespace std;

#define KEY_NOT_IN_PATH "-"
#define EMPTY_PATH ""
#define LEFT_SON '0'
#define RIGHT_SON '1'

template <typename Key>
char get_addition_to_path(Node<Key>* son_node, Node<Key>* parent_node){
  return parent_node->left == son_node ? LEFT_SON : RIGHT_SON;
}

template <typename Key>
string get_path_string(Key key, Node<Key>* curr_node, Node<Key>* parent_node = NULL){
  if (!curr_node) return KEY_NOT_IN_PATH;
  Key curr_key = curr_node->get_key();
  // EMPTY_PATH represents the case the root node is the key
  if (curr_key == key){
    if (!parent_node) return EMPTY_PATH;
    else return string(1, get_addition_to_path(curr_node, parent_node));
  }
  string res;
  res = get_path_string(key, curr_node->left, curr_node);
  if (res == KEY_NOT_IN_PATH){
    res = get_path_string(key, curr_node->right, curr_node);
  }
  if (res != KEY_NOT_IN_PATH && parent_node){
    char addition = get_addition_to_path(curr_node, parent_node);
    res.insert(res.begin(), addition);
  }
  return res;
}

template <typename Key>
Node<Key>* get_node_from_path(Node<Key>* root, string path){
  if (!root) throw "the given tree is empty.";
  if (path == KEY_NOT_IN_PATH) return NULL;
  if (path == EMPTY_PATH) return root;
  Node<Key>* curr_node = root;
  for (char c: path){
    if (c == LEFT_SON) curr_node = curr_node->left;
    else curr_node = curr_node->right;
    if (!curr_node) throw "Illegal path";
  }
  return curr_node;
}

template <typename Key>
Node<Key>* get_lowest_common_ancestor(Node<Key>* root, Node<Key>* node1, Node<Key>* node2){
  string node1_path = get_path_string(node1->get_key(), root);
  if (node1_path == KEY_NOT_IN_PATH) throw "node1 does not exists in the given tree.";
  string node2_path = get_path_string(node2->get_key(), root);
  if (node2_path == KEY_NOT_IN_PATH) throw "node2 does not exists in the given tree.";
  int size1 = node1_path.size();
  int size2 = node2_path.size();
  int i;
  for (i = 0; i < size1 && i < size2; ++i){
    char c1 = node1_path.at(i);
    char c2 = node2_path.at(i);
    if (c1 != c2){
      return get_node_from_path(root, node1_path.substr(0, i));
    }
  }
  if (i == size1){
    return node1;
  }
  return node2;
}
