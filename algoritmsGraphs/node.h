#ifndef NODE_H
#define NODE_H

#include <set>
#include <string>

class Node;
typedef std::set<Node*>::iterator node_iterator;
typedef std::set<Node*>::const_iterator const_node_iterator;

class Node {
private:
    std::string name;
    std::set<Node*> neighbours;

public:
    explicit Node(const std::string& nodeName);

    std::string getName() const;

    node_iterator nb_begin();
    node_iterator nb_end();
    const_node_iterator nb_begin() const;
    const_node_iterator nb_end() const;

    void addNeighbour(Node* neighbour);
    void removeNeighbour(Node* neighbour);
};

#endif
