#include "tests_aux.h"

// --------------------- test is direct ancestor --------------------- //
#define DEFAULT_KEY 6
#define DEFAULT_SIZE 4
#define ROOT_KEY 1
#define LEFT_SON_KEY 2
#define RIGHT_SON_KEY 3
#define LEFT_LEFT_SON_KEY 4

bool test_is_direct_ancestor(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    Node<int>* left = tree.find(LEFT_SON_KEY);
    Node<int>* right = tree.find(RIGHT_SON_KEY);
    Node<int>* left_left = tree.find(LEFT_LEFT_SON_KEY);
    
    ASSERT_TRUE(is_direct_ancestor(left->get_key(), root));
    ASSERT_TRUE(is_direct_ancestor(right->get_key(), root));
    ASSERT_TRUE(is_direct_ancestor(left_left->get_key(), left));
    ASSERT_FALSE(is_direct_ancestor(left_left->get_key(), root));
    ASSERT_FALSE(is_direct_ancestor(ROOT_KEY, left));
    ASSERT_FALSE(is_direct_ancestor(ROOT_KEY, right));
    
    return true;
    
}
// --------------------- test get all ancestors --------------------- //
bool test_ancestors_with_empty_tree(){
    Node<int>* root;
    list<int> res = get_all_ancestors(DEFAULT_KEY, root);
    ASSERT_EMPTY(res);
    return true;
}
bool test_ancestors_when_key_not_in_tree(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    list<int> res = get_all_ancestors(DEFAULT_KEY, root);
    ASSERT_EMPTY(res);
    return true;
}
bool test_ancestors_when_key_is_in_root(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    list<int> res = get_all_ancestors(ROOT_KEY, root);
    ASSERT_EMPTY(res);
    return true;
}
bool test_ancestors_of_example(){
    int root_key = 7;
    list<int> example = {7,3,4,2,5,8,1,6};
    list<int> expected = {2,3,7};
    BinaryTree<int> tree = example_setup(example);
    Node<int>* root = tree.find(root_key);
    list<int> res = get_all_ancestors(DEFAULT_KEY, root);
    ASSERT_EQ(res, expected);
    return true;
}
bool test_get_all_ancestors(){
    inc_indentation();
    RUN_TEST(test_ancestors_with_empty_tree);
    RUN_TEST(test_ancestors_when_key_not_in_tree);
    RUN_TEST(test_ancestors_when_key_is_in_root);
    RUN_TEST(test_ancestors_of_example);
    dec_indentation();
    // RUN_TEST(test_ancestors_with_empty_tree);
    return true;
}

int main()
{
    RUN_TEST(test_is_direct_ancestor);
    RUN_TEST(test_get_all_ancestors);
    return 0;
}
