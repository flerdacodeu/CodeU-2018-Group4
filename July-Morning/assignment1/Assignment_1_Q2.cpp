#include <iostream>

typedef struct node
{
    int data;
    node * next;
} node;

class single_linked_list 
{
    private:
        struct node * head;
        
    public:
        single_linked_list() 
        {
            head = NULL;
        }
        
        ~single_linked_list() 
        {
            while (head != NULL)
            {
                node * temp = head; 
                head = head->next;
                delete head;
            }    
        }

        // Insert element with given data to the beginning of the list
        void insert (int data) 
        {
            node * temp = new node;
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
        }
        
        // Find k-th element from the end of the list
        // Return value:
        // true - if k-th element from the end was found successfully
        // false - if size of the list is less than given k
        bool find_k_from_tail (int k, int& data) 
        {
            node * tail = head;
            node * k_node = head;
            int diff_counter = 0;
            while (tail != NULL)
            {
                tail = tail->next;
                if (diff_counter < (k + 1))
                    diff_counter++;
                else
                    k_node = k_node->next;
            }  
            if (diff_counter < (k + 1))
                return false;
            data = k_node->data;    
            return true;
        }
};

// Run test and print the result 
void Test_K_Search (single_linked_list * list, int k)
{
    int k_list_el;
    if (list->find_k_from_tail(k, k_list_el))
        std::cout << k <<"-th list element from tail is " << k_list_el << std::endl;
    else
        std::cout << "Invalid input: list size is less than given k!" << std::endl;
    return;
}    

int main ()
{
    single_linked_list * test_list = new single_linked_list;
    std::cout << " **** Tests with invalid input **** " << std::endl;
    Test_K_Search (test_list, 0);
    test_list->insert(5);
    Test_K_Search (test_list, 2);
    test_list->insert(10);
    test_list->insert(15);
    Test_K_Search (test_list, 3);
    std::cout << " **** General tests for correctness **** " << std::endl;
    test_list->insert(20);
    test_list->insert(25);
    test_list->insert(30);
    Test_K_Search (test_list, 0);
    Test_K_Search (test_list, 1);
    Test_K_Search (test_list, 2);
    Test_K_Search (test_list, 3);
    Test_K_Search (test_list, 4);
    Test_K_Search (test_list, 5);
    delete test_list;
    return 0;
}
