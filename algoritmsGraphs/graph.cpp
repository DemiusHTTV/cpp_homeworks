#include "graph.h"

Graph::Graph() {}

Graph::Graph(const char* file_name) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Файл не открылся" << endl;
        return;
    }

    string source;
    string target;

    while (file >> source >> target) {
        Node* s;
        Node* t;

        if (nodeMap.find(source) == nodeMap.end()) {
            s = new Node(source);
            addNode(s);
            nodeMap[source] = s;
        } else {
            s = nodeMap[source];
        }

        if (nodeMap.find(target) == nodeMap.end()) {
            t = new Node(target);
            addNode(t);
            nodeMap[target] = t;
        } else {
            t = nodeMap[target];
        }

        addEdge(s, t);
    }
    file.close();
    cout << "Вершин: " << nodes.size() << endl;
}

void Graph::addNode(Node* node) {
    nodes.insert(node);
}

void Graph::addEdge(Node* begin, Node* end) {
    begin->addNeighbour(end);
    end->addNeighbour(begin);
}

Node* Graph::getNode(string name) {
    if (nodeMap.find(name) != nodeMap.end()) {
        return nodeMap[name];
    }
    return NULL;
}

node_iterator Graph::begin() {
    return nodes.begin();
}

node_iterator Graph::end() {
    return nodes.end();
}



void Graph::print() {
    for (node_iterator it = nodes.begin(); it != nodes.end(); it++) {
        cout << (*it)->getName() << ": ";
        for (node_iterator nb = (*it)->nb_begin(); nb != (*it)->nb_end(); nb++) {
            cout << (*nb)->getName() << " ";
        }
        cout << endl;
    }
}

