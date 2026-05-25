#include "graph.h"

int main() {
    Graph graph0("TestGraph.txt");

    vector<Graph> graphs = graph0.findGraphs();

    cout << "Количество графов: " << graphs.size() << endl;

    for (size_t i = 0; i < graphs.size(); i++) {
        cout << "Граф " << i + 1 << endl;
        graphs[i].print();

        string fileName = "1000_comp_1" + to_string(i + 1) + ".txt";
        graphs[i].print2file(fileName);
    }

    return 0;
}