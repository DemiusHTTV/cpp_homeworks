#include "graph.h"

Graph::Graph() {}

Graph::Graph(const Graph& other) {
    copyFrom(other);
}

Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

Graph::Graph(Graph&& other) noexcept {
    nodes = std::move(other.nodes);
    nodeMap = std::move(other.nodeMap);
    other.nodes.clear();
    other.nodeMap.clear();
}

Graph& Graph::operator=(Graph&& other) noexcept {
    if (this != &other) {
        clear();
        nodes = std::move(other.nodes);
        nodeMap = std::move(other.nodeMap);
        other.nodes.clear();
        other.nodeMap.clear();
    }
    return *this;
}

Graph::~Graph() {
    clear();
}

void Graph::clear() {
    for (node_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        delete *it;
    }
    nodes.clear();
    nodeMap.clear();
}

void Graph::copyFrom(const Graph& other) {
    for (const_node_iterator it = other.begin(); it != other.end(); ++it) {
        addNode((*it)->getName());
    }

    for (const_node_iterator it = other.begin(); it != other.end(); ++it) {
        const std::string fromName = (*it)->getName();
        for (const_node_iterator nb = (*it)->nb_begin(); nb != (*it)->nb_end(); ++nb) {
            addEdge(fromName, (*nb)->getName());
        }
    }
}

Node* Graph::addNode(const std::string& name) {
    Node* existing = getNode(name);
    if (existing != 0) {
        return existing;
    }

    Node* node = new Node(name);
    addNode(node);
    return node;
}

void Graph::addNode(Node* node) {
    if (node == 0) {
        return;
    }
    nodes.insert(node);
    nodeMap[node->getName()] = node;
}

void Graph::addEdge(Node* begin, Node* end) {
    if (begin == 0 || end == 0) {
        return;
    }
    begin->addNeighbour(end);
    end->addNeighbour(begin);
}

void Graph::addEdge(const std::string& beginName, const std::string& endName) {
    Node* begin = addNode(beginName);
    Node* end = addNode(endName);
    addEdge(begin, end);
}

Node* Graph::getNode(const std::string& name) {
    std::map<std::string, Node*>::iterator it = nodeMap.find(name);
    if (it == nodeMap.end()) {
        return 0;
    }
    return it->second;
}

const Node* Graph::getNode(const std::string& name) const {
    std::map<std::string, Node*>::const_iterator it = nodeMap.find(name);
    if (it == nodeMap.end()) {
        return 0;
    }
    return it->second;
}

const std::set<Node*>& Graph::getNodes() const {
    return nodes;
}

std::vector<std::string> Graph::getNodeNames() const {
    std::vector<std::string> names;
    for (std::map<std::string, Node*>::const_iterator it = nodeMap.begin(); it != nodeMap.end(); ++it) {
        names.push_back(it->first);
    }
    return names;
}

node_iterator Graph::begin() {
    return nodes.begin();
}

node_iterator Graph::end() {
    return nodes.end();
}

const_node_iterator Graph::begin() const {
    return nodes.begin();
}

const_node_iterator Graph::end() const {
    return nodes.end();
}
