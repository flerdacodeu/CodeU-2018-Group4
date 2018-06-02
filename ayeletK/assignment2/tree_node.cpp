//the expected node structure of the tree node
template <typename Key>
class Node{
  Key key;
public:
  Node* left;
  Node* right;
  
  Node(Key key): Node(key, nullptr, nullptr) {}
  Node(Key key, Node* left, Node* right): key(key), left(left), right(right) {}
  Key get_key(){ return key; }
  bool has_left(){ return left; }
  bool has_right(){ return right; }
  bool is_leaf(){ return !has_left() && !has_right(); }
};
