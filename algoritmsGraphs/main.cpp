#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <vector>
#include <string>
#include <map>
#include "graph.h"

using namespace std;

void print2file(Graph& g, string fileName); 
vector<Graph> findGraphs(Graph& original);

int main() {
    Graph graph0("TestGraph.txt");

    vector<Graph> graphs = findGraphs(graph0);

    cout << "Количество графов: " << graphs.size() << endl;

    for (size_t i = 0; i < graphs.size(); i++) {
        cout << "Граф " << i + 1 << endl;
        graphs[i].print();

        string fileName = "1000_comp_1" + to_string(i + 1) + ".txt";
        print2file(graphs[i], fileName);
    }

    return 0;
}

vector<Graph> findGraphs(Graph& original) {
    vector<Graph> result;
    set<Node*> visited;
    
    set<Node*>& nodes = original.getNodes();
    map<string, Node*>& nodeMap = original.getNodeMap();

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
            g.getNodeMap()[current->getName()] = newNode;

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
                if (g.getNodeMap().find(nbName) != g.getNodeMap().end()) {
                    g.addEdge(
                        g.getNodeMap()[oldNode->getName()],
                        g.getNodeMap()[nbName]
                    );
                }
            }
        }
        result.push_back(g);
    }
    return result;
}

void print2file(Graph& g, string fileName) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << fileName << " для записи" << endl;
        return;
    }
    
    set<string> printed;
    set<Node*>& nodes = g.getNodes();

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
    cout << "Граф сохранен в файл: " << fileName << endl;
}
