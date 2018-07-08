#ifndef DISJOINT_SET_HPP_
#define DISJOINT_SET_HPP_

#include <vector>

// TODO: make implementation more general
class DisjointSet
{
    private:
        int set_num;
        std::vector<int> parent;
        std::vector<int> rank;
        // Find set that inlcudes i
        int find (int i); 
    
    public:
        DisjointSet (int init_set_num);
        // Merge set that includes i and set that includes j accroding to rank
        bool unite (int i, int j);
};

#endif //DISJOINT_SET_HPP_
