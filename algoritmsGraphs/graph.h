#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include "node.h"

class Graph {
private:
    std::set<Node*> nodes;
    std::map<std::string, Node*> nodeMap;

    void clear();
    void copyFrom(const Graph& other);

public:
    Graph();
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    Graph(Graph&& other) noexcept;
    Graph& operator=(Graph&& other) noexcept;
    ~Graph();

    Node* addNode(const std::string& name);
    void addNode(Node* node);

    void addEdge(Node* begin, Node* end);
    void addEdge(const std::string& beginName, const std::string& endName);

    Node* getNode(const std::string& name);
    const Node* getNode(const std::string& name) const;

    const std::set<Node*>& getNodes() const;
    std::vector<std::string> getNodeNames() const;

    node_iterator begin();
    node_iterator end();
    const_node_iterator begin() const;
    const_node_iterator end() const;
};

#endif
