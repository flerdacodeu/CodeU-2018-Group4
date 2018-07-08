#define EXAMPLE_SIZE 4
#include "codeu_test_lib.h"

Map_vec example_vec = { {WATER, LAND,  WATER, LAND},
                        {LAND,  LAND,  WATER, WATER},
                        {WATER, WATER, LAND,  WATER},
                        {WATER, WATER, LAND,  WATER}    };

class Tests{
    Map_vec* _data;
    bool _delete_data;
    Solution _solution;
    
    void example_setup(){
        _data = &example_vec;
    }
    void test_count_islands_zero_islands(){
        Map_vec map_vec = {{WATER}};
        int expected = 0;
        Solution sol = Solution(&map_vec);
        int actual = sol.count_islands();
        EXPECT_EQ(expected, actual);
    }
    void test_count_islands_digonal_islands(){
        Map_vec map_vec = {{LAND,WATER},{WATER,LAND}};
        int expected = 2;
        Solution sol = Solution(&map_vec);
        int actual = sol.count_islands();
        EXPECT_EQ(expected, actual);
    }
    void test_count_islands_example(){
        int expected = 3;
        int actual = _solution.count_islands();
        EXPECT_EQ(expected, actual);
    }
public:
    Tests() {
        example_setup();
        _solution = Solution(_data);
        Map map(_data);
    }
    Tests(Map_vec* map_vec): _data(map_vec), _solution(_data){
        Map map(_data);
    }
    ~Tests(){}
    void run_tests(){
        RUN_TEST(test_count_islands_zero_islands);
        RUN_TEST(test_count_islands_digonal_islands);
        RUN_TEST(test_count_islands_example);
    }
    // for user tests
    void run_test(void (*test_func)()){
        RUN_TEST(test_func);
    }
};

int main()
{
    Tests tests;
    tests.run_tests();
    return 0;
}
