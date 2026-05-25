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

vector<Graph> Graph::findGraphs() {
    vector<Graph> result;
    set<Node*> visited;

    for (node_iterator it = nodes.begin(); it != nodes.end(); it++) {
        Node* start = *it;
        if (visited.find(start) != visited.end()) {
            continue;
        }

        Graph g;
        queue<Node*> q;
        q.push(start);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (visited.find(current) != visited.end()) {
                continue;
            }

            visited.insert(current);
            Node* newNode = new Node(current->getName());
            g.addNode(newNode);
            g.nodeMap[current->getName()] = newNode;

            for (node_iterator nb = current->nb_begin(); nb != current->nb_end(); nb++) {
                if (visited.find(*nb) == visited.end()) {
                    q.push(*nb);
                }
            }
        }

        for (node_iterator nit = g.begin(); nit != g.end(); nit++) {
            Node* oldNode = nodeMap[(*nit)->getName()];
            for (node_iterator nb = oldNode->nb_begin(); nb != oldNode->nb_end(); nb++) {
                string nbName = (*nb)->getName();
                if (g.nodeMap.find(nbName) != g.nodeMap.end()) {
                    g.addEdge(
                        g.nodeMap[oldNode->getName()],
                        g.nodeMap[nbName]
                    );
                }
            }
        }
        result.push_back(g);
    }
    return result;
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

void Graph::print2file(string fileName) {
    ofstream file(fileName);
    set<string> printed;

    for (node_iterator it = nodes.begin(); it != nodes.end(); it++) {
        for (node_iterator nb = (*it)->nb_begin(); nb != (*it)->nb_end(); nb++) {
            string a = (*it)->getName();
            string b = (*nb)->getName();
            string edge;

            if (a < b)
                edge = a + " " + b;
            else
                edge = b + " " + a;

            if (printed.find(edge) == printed.end()) {
                printed.insert(edge);
                file << edge << endl;
            }
        }
    }
    file.close();
}