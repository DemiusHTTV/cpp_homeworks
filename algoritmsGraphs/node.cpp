#include "node.h"

Node::Node(const string& aname) {
    name = aname;
}

string Node::getName() const {
    return name;
}

node_iterator Node::nb_begin() {
    return neighbours.begin();
}

node_iterator Node::nb_end() {
    return neighbours.end();
}

void Node::addNeighbour(Node* neighbour) {
    neighbours.insert(neighbour);
}

void Node::removeNeighbour(Node* neighbour) {
    neighbours.erase(neighbour);
}