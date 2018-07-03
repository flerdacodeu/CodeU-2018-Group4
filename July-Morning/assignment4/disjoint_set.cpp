#include "disjoint_set.hpp"

DisjointSet::DisjointSet (unsigned int init_set_num)
{
    set_num = init_set_num;
    rank = std::vector<unsigned int>(init_set_num);
    parent = std::vector<unsigned int>(init_set_num);
    for (unsigned int i = 0; i < init_set_num; i++)
        parent[i] = i;
}
        
// Find set that inlcudes i
unsigned int DisjointSet::find (unsigned int i)
{
    if (parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}
        
// Merge set that includes i and set that includes j according to ranks
bool DisjointSet::unite (unsigned int i, unsigned int j)
{
    if ((i >= set_num) || (j >= set_num))
        return false;
    unsigned int i_root = find(i);
    unsigned int j_root = find(j);
    if (i_root == j_root)            
        return false;
    if (rank[i_root] < rank[j_root])
    {
        parent[i_root] = j_root;
    } 
    else
    {
        parent[j_root] = i_root;
        if (rank[i_root] == rank[j_root])
            rank[i_root]++;
    }
    return true;
}