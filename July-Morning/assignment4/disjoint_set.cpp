#include <stdexcept>
#include "disjoint_set.hpp"

DisjointSet::DisjointSet (int init_set_num)
{
    if (init_set_num < 0)
        throw std::invalid_argument("received negative value");
    set_num = init_set_num;
    rank = std::vector<int>(init_set_num);
    parent = std::vector<int>(init_set_num);
    for (int i = 0; i < init_set_num; i++)
        parent[i] = i;
}
        
// Find set that inlcudes i
int DisjointSet::find (int i)
{
    if (parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}
        
// Merge set that includes i and set that includes j according to ranks
bool DisjointSet::unite (int i, int j)
{
    if (i >= set_num || j >= set_num)
        return false;
    if (i < 0 || j < 0)
        return false;    
    int i_root = find(i);
    int j_root = find(j);
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
