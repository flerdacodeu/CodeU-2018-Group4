#include <iostream>
#include <string>

template <typename T> struct node
{
    T data;
    node * next;
};

template <typename T> class single_linked_list 
{
    private:
        struct node<T> * head;
        
    public:
        single_linked_list() : head(NULL) {}
        
        ~single_linked_list() 
        {
            while (head != NULL)
            {
                node<T> * temp = head; 
                head = head->next;
                delete temp;
            }    
        }

        // Insert element with given data to the beginning of the list
        void insert (T data) 
        {
            node<T> * temp = new node<T>;
            temp->data = data;
            if (head == NULL)
            {
                temp->next = NULL;
                head = temp;
            }
            else
            {
                temp->next = head;
                head = temp;
            }
            return;
        }
        
        // Find k-th element from the end of the list
        // Return value:
        // true - if k-th element from the end was found successfully
        // false - if size of the list is less than given k or k is negative
        bool find_k_from_tail (int k, T& data) 
        {
            if (k < 0)
                return false;
            node<T> * tail = head;
            node<T> * k_node = head;
            int diff_counter = 0;
            while (tail != NULL && diff_counter < k + 1) 
            {
                tail = tail->next;
                diff_counter++;
            }
            if (diff_counter < (k + 1))
                return false;
            while (tail != NULL) 
            {
                tail = tail->next;
                k_node = k_node->next;
            }   
            data = k_node->data;    
            return true;
        }
};

// Run test and print the result 
template <typename T> void Test_K_Search (single_linked_list<T> * list, int k)
{
    T k_list_el;
    if (list->find_k_from_tail(k, k_list_el))
        std::cout << k <<"-th list element from tail is " << k_list_el << std::endl;
    else
        std::cout << "Invalid input!" << std::endl;
    return;
}    

int main ()
{
    std::cout << " **** Tests for list with int data **** " << std::endl << std::endl;
    single_linked_list<int> * int_test_list = new single_linked_list<int>;
    std::cout << " **** Tests with invalid input **** " << std::endl;
    Test_K_Search (int_test_list, 0);
    int_test_list->insert(5);
    Test_K_Search (int_test_list, 2);
    int_test_list->insert(10);
    int_test_list->insert(15);
    Test_K_Search (int_test_list, 3);
    Test_K_Search (int_test_list, -1);
    Test_K_Search (int_test_list, -100);
    std::cout << " **** General tests for correctness **** " << std::endl;
    int_test_list->insert(20);
    int_test_list->insert(25);
    int_test_list->insert(30);
    Test_K_Search (int_test_list, 0);
    Test_K_Search (int_test_list, 1);
    Test_K_Search (int_test_list, 2);
    Test_K_Search (int_test_list, 3);
    Test_K_Search (int_test_list, 4);
    Test_K_Search (int_test_list, 5);
    delete int_test_list;
    std::cout << std::endl << " **** Tests for list with string data **** " << std::endl << std::endl;
    single_linked_list<std::string> * str_test_list = new single_linked_list<std::string>;
    std::cout << " **** Tests with invalid input **** " << std::endl;
    Test_K_Search (str_test_list, 0);
    str_test_list->insert("5");
    Test_K_Search (str_test_list, 2);
    str_test_list->insert("10");
    str_test_list->insert("15");
    Test_K_Search (str_test_list, 3);
    Test_K_Search (str_test_list, -1);
    Test_K_Search (str_test_list, -100);
    std::cout << " **** General tests for correctness **** " << std::endl;
    str_test_list->insert("20");
    str_test_list->insert("25");
    str_test_list->insert("30");
    Test_K_Search (str_test_list, 0);
    Test_K_Search (str_test_list, 1);
    Test_K_Search (str_test_list, 2);
    Test_K_Search (str_test_list, 3);
    Test_K_Search (str_test_list, 4);
    Test_K_Search (str_test_list, 5);
    delete str_test_list;
    return 0;
}
