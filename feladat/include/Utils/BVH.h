#ifndef BVH_H_
#define BVH_H_

#include "Utils/bounding_box.h"

typedef struct Node {
    Bounding_Box box;

    int object_index, parent_index;
    int child1, child2;

    bool is_leaf;

} Node;

typedef struct Tree {
    Node* nodes;
    int n_nodes;
    int root_index;
} Tree;





#endif /* BVH_H_ */