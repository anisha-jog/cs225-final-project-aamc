#include <iostream>
#include <fstream>
#include "graph.h"
#include "algorithms.hpp"

using namespace std;
using namespace algos;
    
int main() {
    cout << "Building graph..." << endl;
    string dataset = "../web-Google.txt";
    Graph g(dataset, 10000);

    cout << "The graph's size is " << g.getSize() << endl << endl;

    std::vector<Graph::Edge*> edges = g.incidentEdges(g.getVertex(0));
    cout << "The edges connected to the first vertex are: " << endl;
    for (int i = 0; i < (int)(edges.size()); i++) {
        cout << *(edges[i]) << endl;
    }

    cout << endl << "Running bfs traversal..." << endl << endl;

    vector<Vertex> bfs_traversal = bfs(g, g.getVertex(0));

    cout << "The traversal contains " << bfs_traversal.size() << " vertices." << endl;
    cout << "The first 10 vertices in the traversal are: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << bfs_traversal.at(i) << " -> ";
    }
    cout << endl;

    cout << "Traversal complete!" << endl << endl;

    cout << "Running PageRank..." << endl << endl;
    vector<pair<Vertex, double>> vec = pageRank(g, 0.85, 10);

    int num_pages = 10;

    cout << "The first " << num_pages << " pages are:" << endl;
    for (int i = 0; i < (int)vec.size() && i < num_pages; i++) {
        cout << vec[i].first << " " << vec[i].second << endl;
    }

    // vector<vector<double>> adjm = g.getAdjM();

    // for (auto row : adjm) {
    //     for (auto col : row) {
    //         cout << col << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}

