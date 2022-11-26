#include <iostream>
#include <fstream>
#include "graph.h"
#include "algorithms.hpp"

using namespace std;
using namespace algos;
    
int main() {
    cout << "Building graph..." << endl;
    ifstream dataset("../web-Google.txt");
    // string dataread;
    // if (dataset.is_open()) {
    //     dataset >> dataread;
    //     cout << dataread << endl;
    // }
    Graph g(dataset);

    cout << "The graph's size is " << g.getSize() << endl;

    std::vector<Graph::Edge*> edges = g.incidentEdges(g.getVertex(0));
    cout << "The edges connected to the first vertex are: " << endl;
    for (int i = 0; i < (int)(edges.size()); i++) {
        cout << *(edges[i]) << endl;
    }

    cout << "Running bfs traversal..." << endl;

    vector<Vertex> bfs_traversal = bfs(g, g.getVertex(0));

    cout << "The traversal contains " << bfs_traversal.size() << " vertices." << endl;
    cout << "The first 100 vertices in the traversal are: " << endl;
    for (int i = 0; i < 100; i++) {
        cout << bfs_traversal.at(i) << " -> ";
    }
    cout << endl;

    cout << "Traversal complete!" << endl;
    return 0;
}