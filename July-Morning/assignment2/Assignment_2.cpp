#include <iostream>
#include <string>
#include <list>

template <typename T> struct node
{
    T key;
    node * left;
    node * right;
    node (T init_key)
    {
        key = init_key;
        left = NULL;
        right = NULL;
    }
};

// Here we assume that all keys in the tree are unique
template <typename T> class binary_tree 
{
    private:
    
        void destroy (node<T> * s_root) 
        {
            if (s_root->left != NULL)
                destroy (s_root->left);
            if (s_root->right != NULL)
                destroy (s_root->right);
            delete s_root;   
        }
        
        // Here we assume that node is NOT its own descendant
        bool is_descendant (T& key, node<T> * parent) 
        {
            if (parent == NULL)
                return false;
            if (parent->left != NULL)    
                if (parent->left->key == key)
                    return true;
            if (parent->right != NULL)    
                if (parent->right->key == key)
                    return true;        
            return is_descendant (key, parent->left) || is_descendant (key, parent->right);
        }
        
    public:
    
        node<T> * root;
        
        binary_tree() : root (NULL) {}
        
        ~binary_tree()
        {
            if (root != NULL)
                destroy (root);
        }
    
        // Find ancestors of the node with a given key
        // Return value:
        // true - if ancestors were found successfully
        // false - if tree is empty or node with given key does not exist
        bool find_ancestors (node<T> * s_root, T& key, std::list<node<T> *>& ancestors) 
        {
            if (s_root == NULL)
                return false;
            if (s_root->key == key)
                return true;
            bool is_ancestor = find_ancestors (s_root->left, key, ancestors) || find_ancestors (s_root->right, key, ancestors);    
            if (is_ancestor)
                ancestors.push_back (s_root);  
            return is_ancestor;    
        }
        
        // Find lowest common ancestor of the nodes with given keys
        // Return value:
        // true - if ancestor was found successfully
        // false - if tree is empty or node with at least one of the given keys does not exist
        // ...or one of the given keys is at the root of the tree
        bool find_lowest_common_ancestor (node<T> * s_root, T& key_1, T& key_2, T& lca_key) 
        {
            if (s_root == NULL)
                return false;
            bool left = find_lowest_common_ancestor (s_root->left, key_1, key_2, lca_key);
            if (left)
                return true;
            bool right = find_lowest_common_ancestor (s_root->right, key_1, key_2, lca_key);
            if (right)
                return true;
            if (is_descendant (key_1, s_root) && is_descendant (key_2, s_root))
            {
                lca_key = s_root->key;
                return true;
            }
            return false;
        }
};

// Run test and print the result 
template <typename T> void Test_Find_Ancestors (binary_tree<T> * b_tree, T key)
{
    std::list<node<T> *> ancestors;
    if (b_tree->find_ancestors (b_tree->root, key, ancestors))
    {
        std::cout << "Ancestors of node with key " << key << " are: ";
        for (node<T> * a : ancestors)
            std::cout << a->key << " ";
        std::cout << std::endl;
    }    
    else
        std::cout << "Invalid input!" << std::endl;
    return;
}  

// Run test and print the result 
template <typename T> void Test_Find_Lowest_Common_Ancestor (binary_tree<T> * b_tree, T key_1, T key_2)
{
    T lca;
    if (b_tree->find_lowest_common_ancestor (b_tree->root, key_1, key_2, lca))
        std::cout << "Lowest common ancestor of node with key " << key_1 << " and node with key " << key_2 << " is: " << lca << std::endl;
    else
        std::cout << "Invalid input!" << std::endl;
    return;
}   

// Create a tree for testing with int nodes
// If non-empty tree is passed return with no changes
void Create_Test_Int_Tree_From_Empty_Or_Return (binary_tree<int> * b_tree)
{
    if (b_tree->root != NULL)
        return;
    b_tree->root = new node<int>(7);
    b_tree->root->left = new node<int>(3);
    b_tree->root->left->left = new node<int>(2);
    b_tree->root->left->left->left = new node<int>(1);
    b_tree->root->left->left->right = new node<int>(6);
    b_tree->root->left->right = new node<int>(5);
    b_tree->root->right = new node<int>(4);
    b_tree->root->right->right = new node<int>(8);
}

int main ()
{
    std::cout << " **** Tests for tree with int data **** " << std::endl << std::endl;
    binary_tree<int> * test_binary_tree = new binary_tree<int>;
    std::cout << " **** Tests with empty tree **** " << std::endl;
    Test_Find_Ancestors (test_binary_tree, 1);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 1, 2);
    std::cout << " **** Tests with invalid input **** " << std::endl;
    Create_Test_Int_Tree_From_Empty_Or_Return (test_binary_tree);
    Test_Find_Ancestors (test_binary_tree, 0);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 1, 0);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 0, 1);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 0, 9);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 7, 4);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 6, 7);
    std::cout << " **** General tests for correctness **** " << std::endl;
    Test_Find_Ancestors (test_binary_tree, 7);
    Test_Find_Ancestors (test_binary_tree, 8);
    Test_Find_Ancestors (test_binary_tree, 2);
    Test_Find_Ancestors (test_binary_tree, 5);
    Test_Find_Ancestors (test_binary_tree, 6);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 3, 4);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 1, 5);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 6, 8);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 8, 4);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 6, 5);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 6, 1);
    Test_Find_Lowest_Common_Ancestor (test_binary_tree, 2, 5);
    delete test_binary_tree;
    return 0;
}
