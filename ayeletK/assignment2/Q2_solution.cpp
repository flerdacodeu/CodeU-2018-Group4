#include "tree_node.cpp"
#include "my_exceptions.cpp"
#include <string>

using namespace std;

#define PATH_EXISTS true
#define PATH_DOESNT_EXISTS false
#define EMPTY_PATH ""
#define LEFT_SON '0'
#define RIGHT_SON '1'

template <typename Key>
bool get_path_string(Key key, Node<Key>* curr_node, string* path){
  if (!curr_node) return PATH_DOESNT_EXISTS;
  Key curr_key = curr_node->get_key();
  if (curr_key == key){
    *path = EMPTY_PATH; // EMPTY_PATH represents the case the root node is the key
    return PATH_EXISTS;
  }
  bool path_exists = get_path_string(key, curr_node->left, path);
  if (path_exists){
      path->insert(path->begin(), LEFT_SON);
      return PATH_EXISTS;
  }
  path_exists = get_path_string(key, curr_node->right, path);
  if (path_exists){
      path->insert(path->begin(), RIGHT_SON);
      return PATH_EXISTS;
  }
  return PATH_DOESNT_EXISTS;
}

template <typename Key>
Node<Key>* get_node_from_path(Node<Key>* root, string path){
  if (!root) throw emptyTreeException();
  Node<Key>* curr_node = root;
  for (char c: path){
      if (c == LEFT_SON) curr_node = curr_node->left;
      else if (c == RIGHT_SON) curr_node = curr_node->right;
      else throw illegalPathException(); // case there is illegal char in path string
      if (!curr_node) throw illegalPathException(); // case path leads to null node
  }
  return curr_node;
}

template <typename Key>
void get_nodes_paths(Node<Key>* root, Node<Key>* node1, Node<Key>* node2, string* path1, string* path2){
    bool node1_path_exists = get_path_string(node1->get_key(), root, path1);
    if (!node1_path_exists) throw nodeNotExistsException("node1");
    bool node2_path_exists = get_path_string(node2->get_key(), root, path2);
    if (!node2_path_exists) throw nodeNotExistsException("node2");
}

template <typename Key>
Node<Key>* get_lowest_common_ancestor(Node<Key>* root, Node<Key>* node1, Node<Key>* node2){
  if (!root) throw emptyTreeException();
  if (!node1 || !node2) throw nullNodeException();
  string node1_path, node2_path;
  get_nodes_paths(root, node1, node2, &node1_path, &node2_path);
  int size1 = node1_path.size();
  int size2 = node2_path.size();
  int i;
  for (i = 0; i < size1 && i < size2; ++i){
      char c1 = node1_path.at(i);
      char c2 = node2_path.at(i);
      if (c1 != c2) return get_node_from_path(root, node1_path.substr(0, i));
  }
  if (i == size1) return node1;
  return node2;
}
