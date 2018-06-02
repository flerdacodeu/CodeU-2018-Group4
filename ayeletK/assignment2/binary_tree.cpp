// I implemented this class but did not use it in mt assignment solution.
// I thought the node class wa enough

#include <list>

template <typename Key>
class BinaryTree {
  Node<Key>* root;
  
  void insert_in_next_free_position(Node<Key>* new_node){
    list<Node<Key>*> tree_nodes;
    tree_nodes.push_back(root);
    Node<Key>* curr_node;
    while (!tree_nodes.empty()){
      curr_node = tree_nodes.front();
      if (!curr_node->has_left()){
        curr_node->left = new_node;
        return;
      }
      if (!curr_node->has_right()){
        curr_node->right = new_node;
        return;
      }
      tree_nodes.push_back(curr_node->left);
      tree_nodes.push_back(curr_node->right);
      tree_nodes.pop_front();
    }
  }
  void destroy_binary_tree(Node<Key>* curr_node){
    if (!curr_node){
      destroy_binary_tree(curr_node->left);
      destroy_binary_tree(curr_node->right);
      delete(curr_node);
    }
  }
  Node<Key>* find(Key key, Node<Key>* curr_node){
    if (!curr_node) return nullptr;
    if (curr_node->get_key() == key) return curr_node;
    Node<Key>* left_find_res = find(key, curr_node->left);
    if (left_find_res) return left_find_res;
    return find(key, curr_node->right);
  }
public:
  BinaryTree(): root(nullptr) {}
  ~BinaryTree() {
    destroy_binary_tree(root);
    root = nullptr;
  }
  void insert_node(Key key){
    if (find(key)) throw "Element with the given key already exists in the tree";
    Node<Key>* new_node = new Node<Key>(key);
    if (!root) root = new_node;
    else insert_in_next_free_position(new_node);
  }
  Node<Key>* find(Key key){
    return find(key, root);
  }
};
