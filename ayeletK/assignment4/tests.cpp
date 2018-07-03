#define EXAMPLE_SIZE 4
#define ONE 1
#define TWO 2
#include "codeu_test_lib.h"


vector<vector<bool>> example_vec = {    {WATER, LAND,  WATER, LAND},
                                        {LAND,  LAND,  WATER, WATER},
                                        {WATER, WATER, LAND,  WATER},
                                        {WATER, WATER, LAND,  WATER}    };
class Tests{
    int _rows;
    int _cols;
    bool** _data;
    DFS<bool> _dfs;
    bool _delete_data;
    Solution _solution;
    
    void example_setup(){
        _rows = EXAMPLE_SIZE;
        _cols = EXAMPLE_SIZE;
        _data = new bool*[EXAMPLE_SIZE];
        
        for (int row = 0; row < _rows; ++row){
            _data[row] = new bool[EXAMPLE_SIZE];
            for (int col = 0; col < _cols; ++col){
                _data[row][col] = example_vec[row][col];
            }
        }
        
    }
    bool test_count_islands_zero_islands(){
        bool map[ONE][ONE] = {{WATER}};
        int expected = 0;
        _solution = Solution(ONE, ONE, (bool**) map);
        int actual = _solution.count_islands();
        EXPECT_EQ(expected, actual);
        return true;
    }
    bool test_count_islands_digonal_islands(){
        bool map[TWO][TWO] = {{LAND,WATER},{WATER,LAND}};
        int expected = 2;
        _solution = Solution(ONE, ONE, (bool**) map);
        int actual = _solution.count_islands();
        EXPECT_EQ(expected, actual);
        return true;
    }
    bool test_count_islands_example(){
        int expected = 3;
        int actual = _solution.count_islands();
        EXPECT_EQ(expected, actual);
        return true;
    }
public:
    Tests(): _dfs(LAND) {
        example_setup();
        _delete_data = true;
        _solution = Solution(_rows, _cols, _data);
    }
    Tests(int rows, int cols, bool** data): _rows(rows), _cols(cols), _data(data), _dfs(LAND), _solution(rows,cols,data){
        _delete_data = false;
    }
    ~Tests(){
        if (_delete_data) {
            for (int row = 0; row < _rows; ++row){
                delete _data[row];
            }
            delete _data;
        }
    }
    void run_tests(){
        RUN_TEST(test_count_islands_zero_islands);
        RUN_TEST(test_count_islands_digonal_islands);
        RUN_TEST(test_count_islands_example);
    }
    // for user tests
    void run_test(bool (*test_func)()){
        RUN_TEST(test_func);
    }
};

int main()
{
    Tests tests;
    tests.run_tests();
    return 0;
}
