#include <iostream>
#include <set>
#include <queue>
#include <string>
#include "node.h"
#include "graph.h"



// ================= BFS =================
bool BFS(Node* start, Node* target) {
    std::queue<Node*> q;
    std::set<Node*> visited;

    q.push(start);

    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();

        if (cur == target) return true;

        if (visited.count(cur)) continue;
        visited.insert(cur);

        for (auto n = cur->begin(); n != cur->end(); ++n) {
            q.push(*n);
        }
    }

    return false;
}


// ================= DFS =================
bool DFS(Node* cur, Node* target, std::set<Node*>& visited) {
    if (cur == target) return true;

    visited.insert(cur);

    for (auto n = cur->begin(); n != cur->end(); ++n) {
        if (!visited.count(*n)) {
            if (DFS(*n, target, visited)) return true;
        }
    }

    return false;
}

    
static void printDijkstra(const Graph& g, const std::string& startName) {
    Node* start = g.getNode(startName);
    if (start == nullptr) {
        std::cout << "Вершина " << startName << " не найдена.\n";
        return;
    }

    auto dist = g.dijkstra(start);
    std::cout << "\nДейкстра от вершины " << startName << ":\n";
    for (const auto& p : g.getNodes()) {
        Node* node = p.second;
        std::cout << startName << " -> " << node->getName() << " = ";
        if (dist[node] == std::numeric_limits<int>::max()) {
            std::cout << "INF";
        } else {
            std::cout << dist[node];
        }
        std::cout << '\n';
    }
}

// ================= MAIN =================
int main() {
    Graph g;

    Node* a = new Node("A");
    Node* b = new Node("B");
    Node* c = new Node("C");
    Node* d = new Node("D");

    g.addNode(a);
    g.addNode(b);
    g.addNode(c);
    g.addNode(d);

    g.addEdge(a, b);
    g.addEdge(b, c);
    g.addEdge(c, d);

    std::cout << "BFS A->D: " << BFS(a, d) << std::endl;

    std::set<Node*> visited;
    std::cout << "DFS A->D: " << DFS(a, d, visited) << std::endl;
    
    std::cout << "\n===== DIJKSTRA =====" << std::endl;
    printDijkstra(g, "A");

    return 0;
}