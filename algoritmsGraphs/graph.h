#pragma once
#include <string>
#include <set>  
#include "node.h"
class Graph {
    std::set<Node*> nodes;

public:
    void addNode(Node* n) {
        nodes.insert(n);
    }

    void addEdge(Node* a, Node* b) {
        a->addNeighbour(b);
        b->addNeighbour(a);
    }
};
