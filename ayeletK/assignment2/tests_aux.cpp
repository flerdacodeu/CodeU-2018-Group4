#include <exception>
#include "binary_tree.cpp"

int level = 0;
string indentation;
bool passed;

#define RUN_TEST(test) \
    do { cout << indentation << "Running " << #test << "..." << endl; \
    if (test()){ cout << indentation << "--PASSED--" << endl; } \
    else cout << indentation << "--FAILED--" << endl; \
    } while(0)
#define ASSERT_TRUE(res) \
    assert(res == true)
#define ASSERT_FALSE(res) \
    assert(res == false)
#define ASSERT_NULL(res) \
    assert(res == NULL)
#define ASSERT_EQ(res,exp) \
    assert(res == exp)
#define ASSERT_NOT_EQ(res,exp) \
    assert(res != exp)
#define ASSERT_EMPTY(collection) \
    assert(collection.empty())
#define ASSERT_EXCEPTION_WAS_THROWN(expression, exception_type) \
    passed = false; \
    try{ \
        expression; \
    } catch(exception_type&){ \
        passed = true; \
    } \
    ASSERT_TRUE(passed)
    
void inc_indentation(){
    ++level;
    indentation = string(level, '\t');
}
void dec_indentation(){
    --level;
    indentation = string(level, '\t');
}

BinaryTree<int> basic_setup(int size){
    BinaryTree<int> tree;
    for (int i = 1; i<= size; ++i){
        tree.insert_node(i);
    }
    return tree;
}

// build tree from specific axample
BinaryTree<int> example_setup(list<int> example){
    BinaryTree<int> tree;
    for (int key: example){
        tree.insert_node(key);
    }
    return tree;
}
