#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <fstream>
#include <map>
#include "node.h"

using namespace std;

class Graph {
private:
    set<Node*> nodes;
    map<string, Node*> nodeMap;

public:
    Graph();
    Graph(const char* file_name);

    void addNode(Node* node);
    void addEdge(Node* begin, Node* end);

    Node* getNode(string name);

    node_iterator begin();
    node_iterator end();


    void print();
 
};

#endif
