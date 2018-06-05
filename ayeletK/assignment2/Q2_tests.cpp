#include "tests_aux.h"

// --------------------- test get addition to path --------------------- //
bool test_addition_for_left_son(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    Node<int>* left = tree.find(LEFT_SON_KEY);
    char res = get_addition_to_path(left, root);
    ASSERT_EQ(res, LEFT_SON);
    return true;
}
bool test_addition_for_right_son(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    Node<int>* right = tree.find(RIGHT_SON_KEY);
    char res = get_addition_to_path(right, root);
    ASSERT_EQ(res, RIGHT_SON);
    return true;
}
bool test_get_addition_to_path(){
    inc_indentation();
    RUN_TEST(test_addition_for_left_son);
    RUN_TEST(test_addition_for_right_son);
    dec_indentation();
    return true;
}
// --------------------- test get path string --------------------- //
bool test_get_path_of_empty_tree(){
    Node<int>* root;
    string res = get_path_string(DEFAULT_KEY, root);
    ASSERT_EQ(res, KEY_NOT_IN_PATH);
    return true;
}
bool test_get_path_of_key_not_in_tree(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    string res = get_path_string(DEFAULT_KEY, root);
    ASSERT_EQ(res, KEY_NOT_IN_PATH);
    return true;
}
bool test_get_path_of_root(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    string res = get_path_string(ROOT_KEY, root);
    ASSERT_EQ(res, EMPTY_PATH);
    return true;
}
bool test_get_path_of_non_root_node(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    string expected = string() + LEFT_SON + LEFT_SON;
    string res = get_path_string(LEFT_LEFT_SON_KEY, root);
    ASSERT_EQ(res, expected);
    return true;
}
bool test_get_path_string(){
    inc_indentation();
    RUN_TEST(test_get_path_of_empty_tree);
    RUN_TEST(test_get_path_of_key_not_in_tree);
    RUN_TEST(test_get_path_of_root);
    RUN_TEST(test_get_path_of_non_root_node);
    dec_indentation();
    return true;
}
// --------------------- test get node from path --------------------- //
bool test_get_node_path_of_empty_tree(){
    Node<int>* root;
    ASSERT_EXCEPTION_WAS_THROWN(get_node_from_path(root, KEY_NOT_IN_PATH), emptyTreeException);
    ASSERT_EXCEPTION_WAS_THROWN(get_node_from_path(root, EMPTY_PATH), emptyTreeException);
    ASSERT_EXCEPTION_WAS_THROWN(get_node_from_path(root, string()+RIGHT_SON+LEFT_SON), emptyTreeException);
    return true;
}
bool test_get_node_path_of_KEY_NOT_IN_PATH(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    Node<int>* res = get_node_from_path(root, KEY_NOT_IN_PATH);
    ASSERT_NULL(res);
    return true;
}
bool test_get_node_path_of_EMPTY_PATH(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    Node<int>* res = get_node_from_path(root, EMPTY_PATH);
    ASSERT_EQ(res, root);
    return true;
}

bool test_get_left_son_from_path(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    Node<int>* left = tree.find(LEFT_SON_KEY);
    string left_son_path = string() + LEFT_SON;
    Node<int>* res = get_node_from_path(root, left_son_path);
    ASSERT_EQ(res, left);
    return true;
}
bool test_get_right_son_from_path(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    Node<int>* right = tree.find(RIGHT_SON_KEY);
    string right_son_path = string() + RIGHT_SON;
    Node<int>* res = get_node_from_path(root, right_son_path);
    ASSERT_EQ(res, right);
    return true;
}
bool test_get_left_left_son_from_path(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    Node<int>* left_left = tree.find(LEFT_LEFT_SON_KEY);
    string left_left_son_path = string() + LEFT_SON + LEFT_SON;
    Node<int>* res = get_node_from_path(root, left_left_son_path);
    ASSERT_EQ(res, left_left);
    return true;
}
bool test_get_non_root_node_path(){
    inc_indentation();
    RUN_TEST(test_get_left_son_from_path);
    RUN_TEST(test_get_right_son_from_path);
    RUN_TEST(test_get_left_left_son_from_path);
    dec_indentation();
    return true;
}
bool test_get_node_path(){
    inc_indentation();
    RUN_TEST(test_get_node_path_of_empty_tree);
    RUN_TEST(test_get_node_path_of_KEY_NOT_IN_PATH);
    RUN_TEST(test_get_node_path_of_EMPTY_PATH);
    RUN_TEST(test_get_non_root_node_path);
    dec_indentation();
    return true;
}

// --------------------- test get lowest common ancestor --------------------- //

// lca represents in this context - lowest common ancestor.
#define FUNC_CALL get_lowest_common_ancestor(root,node1,node2)
bool test_get_lca_for_empty_tree_and_null_nodes(){
    Node<int>* root;
    Node<int>* node1;
    Node<int>* node2;
    ASSERT_EXCEPTION_WAS_THROWN(FUNC_CALL, emptyTreeException);
    return true;
}
bool test_get_lca_for_empty_tree_and_not_null_nodes(){
    Node<int>* root;
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* node1 = tree.find(LEFT_SON_KEY);
    Node<int>* node2 = tree.find(RIGHT_SON_KEY);
    ASSERT_EXCEPTION_WAS_THROWN(FUNC_CALL, emptyTreeException);
    return true;
}
bool test_get_lca_for_empty_tree(){
    inc_indentation();
    RUN_TEST(test_get_lca_for_empty_tree_and_null_nodes);
    RUN_TEST(test_get_lca_for_empty_tree_and_not_null_nodes);
    dec_indentation();
    return true;
}
bool test_get_lca_with_node1_null(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    Node<int>* node1;
    Node<int>* node2;
    ASSERT_EXCEPTION_WAS_THROWN(FUNC_CALL,nullNodeException);
    return true;
}
bool test_get_lca_with_node2_null(){
    BinaryTree<int> tree = basic_setup(DEFAULT_SIZE);
    Node<int>* root = tree.find(ROOT_KEY);
    Node<int>* node1 = tree.find(LEFT_SON_KEY);
    Node<int>* node2;
    ASSERT_EXCEPTION_WAS_THROWN(FUNC_CALL,nullNodeException);
    return true;
}
bool test_get_lca_with_null_node(){
    inc_indentation();
    RUN_TEST(test_get_lca_with_node1_null);
    RUN_TEST(test_get_lca_with_node2_null);
    dec_indentation();
    return true;
}
bool test_get_lca_with_node1_not_in_tree(){
    int size = 1;
    BinaryTree<int> tree = basic_setup(size);
    Node<int>* root = tree.find(ROOT_KEY);
    Node<int>* node1 = new Node<int>(LEFT_SON_KEY);
    Node<int>* node2 = node1;
    ASSERT_EXCEPTION_WAS_THROWN(FUNC_CALL,nodeNotExistsException);
    delete(node1);
    return true;
}
bool test_get_lca_with_node2_not_in_tree(){
    int size = 2;
    BinaryTree<int> tree = basic_setup(size);
    Node<int>* root = tree.find(ROOT_KEY);
    Node<int>* node1 = tree.find(LEFT_SON_KEY);
    Node<int>* node2 = new Node<int>(RIGHT_SON_KEY);
    ASSERT_EXCEPTION_WAS_THROWN(FUNC_CALL,nodeNotExistsException);
    delete(node2);
    return true;
}
bool test_get_lca_with_node_not_in_tree(){
    inc_indentation();
    RUN_TEST(test_get_lca_with_node1_not_in_tree);
    RUN_TEST(test_get_lca_with_node2_not_in_tree);
    dec_indentation();
    return true;
}
bool test_get_lca_of_example(){
    int root_key = 7;
    int lca_key = 3;
    int node1_key = 6;
    int node2_key = 5;
    list<int> example = {7,3,4,2,5,8,1,6};
    BinaryTree<int> tree = example_setup(example);
    Node<int>* root = tree.find(root_key);
    Node<int>* expected_lca = tree.find(lca_key);
    Node<int>* node1 = tree.find(node1_key);
    Node<int>* node2 = tree.find(node2_key);
    Node<int>* res = get_lowest_common_ancestor(root, node1, node2);
    ASSERT_EQ(res, expected_lca);
    return true;
}
bool test_get_lowest_common_ancestor(){
    inc_indentation();
    RUN_TEST(test_get_lca_for_empty_tree);
    RUN_TEST(test_get_lca_with_null_node);
    RUN_TEST(test_get_lca_with_node_not_in_tree);
    RUN_TEST(test_get_lca_of_example);
    dec_indentation();
    return true;
}

int main()
{
    RUN_TEST(test_get_addition_to_path);
    RUN_TEST(test_get_path_string);
    RUN_TEST(test_get_node_path);
    RUN_TEST(test_get_lowest_common_ancestor);
    return 0;
}
