#include "node.h"

Node::Node(const std::string& nodeName) : name(nodeName) {}

std::string Node::getName() const {
    return name;
}

node_iterator Node::nb_begin() {
    return neighbours.begin();
}

node_iterator Node::nb_end() {
    return neighbours.end();
}

const_node_iterator Node::nb_begin() const {
    return neighbours.begin();
}

const_node_iterator Node::nb_end() const {
    return neighbours.end();
}

void Node::addNeighbour(Node* neighbour) {
    if (neighbour != 0) {
        neighbours.insert(neighbour);
    }
}

void Node::removeNeighbour(Node* neighbour) {
    neighbours.erase(neighbour);
}
