#ifndef DISJOINT_SET_HPP_
#define DISJOINT_SET__HPP_

#include <vector>

class DisjointSet
{
    private:
        unsigned int set_num;
        std::vector<unsigned int> parent;
        std::vector<unsigned int> rank;
        // Find set that inlcudes i
        unsigned int find (unsigned int i); 
    
    public:
        DisjointSet (unsigned int init_set_num);
        // Merge set that includes i and set that includes j accroding to rank
        bool unite (unsigned int i, unsigned int j);
};

#endif //DISJOINT_SET_HPP_
