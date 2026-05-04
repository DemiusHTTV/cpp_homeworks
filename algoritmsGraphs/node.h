#pragma once
class Node {
    std::string name;
    std::set<Node*> neighbours;

public:
    Node(const std::string& n) : name(n) {}

    void addNeighbour(Node* n) {
        neighbours.insert(n);
    }

    const std::string& getName() const {
        return name;
    }

    std::set<Node*>::iterator begin() { return neighbours.begin(); }
    std::set<Node*>::iterator end() { return neighbours.end(); }
};
