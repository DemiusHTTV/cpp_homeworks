#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "graph.h"

Graph readGraphFromFile(const std::string& fileName);
void printGraph(const Graph& graph);
void print2file(const Graph& graph, const std::string& fileName);

std::vector<std::string> bfs(const Graph& graph, const std::string& startName);
std::vector<std::string> dfs(const Graph& graph, const std::string& startName);
std::map<std::string, int> dijkstra(const Graph& graph, const std::string& startName);
std::vector<Graph> findGraphs(const Graph& original);

int main(int argc, char* argv[]) {
    std::string inputFile = "TestGraph.txt";
    if (argc > 1) {
        inputFile = argv[1];
    }

    Graph graph = readGraphFromFile(inputFile);
    std::vector<Graph> components = findGraphs(graph);

    std::cout << "Количество графов: " << components.size() << std::endl;

    for (size_t i = 0; i < components.size(); ++i) {
        std::cout << "Граф " << i + 1 << std::endl;
        printGraph(components[i]);

        std::string fileName = "component_" + std::to_string(i) + ".txt";
        print2file(components[i], fileName);
    }

    return 0;
}

Graph readGraphFromFile(const std::string& fileName) {
    Graph graph;
    std::ifstream file(fileName.c_str());

    if (!file.is_open()) {
        std::cout << "Файл не открылся: " << fileName << std::endl;
        return graph;
    }

    std::string source;
    std::string target;

    while (file >> source >> target) {
        graph.addEdge(source, target);
    }

    std::cout << "Вершин: " << graph.getNodes().size() << std::endl;
    return graph;
}

void printGraph(const Graph& graph) {
    for (const_node_iterator it = graph.begin(); it != graph.end(); ++it) {
        std::cout << (*it)->getName() << ": ";
        for (const_node_iterator nb = (*it)->nb_begin(); nb != (*it)->nb_end(); ++nb) {
            std::cout << (*nb)->getName() << " ";
        }
        std::cout << std::endl;
    }
}

void print2file(const Graph& graph, const std::string& fileName) {
    std::ofstream file(fileName.c_str());
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл " << fileName << " для записи" << std::endl;
        return;
    }

    std::set<std::string> printed;

    for (const_node_iterator it = graph.begin(); it != graph.end(); ++it) {
        for (const_node_iterator nb = (*it)->nb_begin(); nb != (*it)->nb_end(); ++nb) {
            std::string a = (*it)->getName();
            std::string b = (*nb)->getName();
            std::string edge = (a < b) ? (a + " " + b) : (b + " " + a);

            if (printed.find(edge) == printed.end()) {
                printed.insert(edge);
                file << edge << std::endl;
            }
        }
    }

    std::cout << "Граф сохранен в файл: " << fileName << std::endl;
}

std::vector<std::string> bfs(const Graph& graph, const std::string& startName) {
    std::vector<std::string> order;
    const Node* start = graph.getNode(startName);
    if (start == 0) {
        return order;
    }

    std::set<const Node*> visited;
    std::queue<const Node*> q;
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        const Node* current = q.front();
        q.pop();
        order.push_back(current->getName());

        for (const_node_iterator nb = current->nb_begin(); nb != current->nb_end(); ++nb) {
            if (visited.find(*nb) == visited.end()) {
                visited.insert(*nb);
                q.push(*nb);
            }
        }
    }

    return order;
}

std::vector<std::string> dfs(const Graph& graph, const std::string& startName) {
    std::vector<std::string> order;
    const Node* start = graph.getNode(startName);
    if (start == 0) {
        return order;
    }

    std::set<const Node*> visited;
    std::stack<const Node*> st;
    st.push(start);

    while (!st.empty()) {
        const Node* current = st.top();
        st.pop();

        if (visited.find(current) != visited.end()) {
            continue;
        }

        visited.insert(current);
        order.push_back(current->getName());

        for (const_node_iterator nb = current->nb_begin(); nb != current->nb_end(); ++nb) {
            if (visited.find(*nb) == visited.end()) {
                st.push(*nb);
            }
        }
    }

    return order;
}

std::map<std::string, int> dijkstra(const Graph& graph, const std::string& startName) {
    // В этом проекте ребра невзвешенные, поэтому каждое ребро считается с весом 1.
    std::map<std::string, int> distance;
    std::vector<std::string> names = graph.getNodeNames();

    for (size_t i = 0; i < names.size(); ++i) {
        distance[names[i]] = INT_MAX;
    }

    const Node* start = graph.getNode(startName);
    if (start == 0) {
        return distance;
    }

    typedef std::pair<int, const Node*> QueueItem;
    std::priority_queue<QueueItem, std::vector<QueueItem>, std::greater<QueueItem> > pq;

    distance[start->getName()] = 0;
    pq.push(QueueItem(0, start));

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        const Node* current = pq.top().second;
        pq.pop();

        if (currentDistance != distance[current->getName()]) {
            continue;
        }

        for (const_node_iterator nb = current->nb_begin(); nb != current->nb_end(); ++nb) {
            int newDistance = currentDistance + 1;
            std::string nbName = (*nb)->getName();

            if (newDistance < distance[nbName]) {
                distance[nbName] = newDistance;
                pq.push(QueueItem(newDistance, *nb));
            }
        }
    }

    return distance;
}

std::vector<Graph> findGraphs(const Graph& original) {
    std::vector<Graph> result;
    std::set<const Node*> visited;

    for (const_node_iterator it = original.begin(); it != original.end(); ++it) {
        const Node* start = *it;
        if (visited.find(start) != visited.end()) {
            continue;
        }

        Graph component;
        std::queue<const Node*> q;
        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            const Node* current = q.front();
            q.pop();
            component.addNode(current->getName());

            for (const_node_iterator nb = current->nb_begin(); nb != current->nb_end(); ++nb) {
                component.addNode((*nb)->getName());
                component.addEdge(current->getName(), (*nb)->getName());

                if (visited.find(*nb) == visited.end()) {
                    visited.insert(*nb);
                    q.push(*nb);
                }
            }
        }

        result.push_back(std::move(component));
    }

    return result;
}
