#pragma once
#include <string>
#include <map>

class Node {
private:
    std::string name;
    std::map<Node*, int> neighbors;

public:
    Node(const std::string& nodeName) : name(nodeName) {}

    std::string getName() const {
        return name;
    }

    void addNeighbor(Node* neighbor, int weight = 1) {
        neighbors[neighbor] = weight;
    }

    auto begin() { return neighbors.begin(); }
    auto end() { return neighbors.end(); }
    auto begin() const { return neighbors.begin(); }
    auto end() const { return neighbors.end(); }
};