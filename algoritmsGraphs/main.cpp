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

    return 0;
}