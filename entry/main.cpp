#include <iostream>
#include <fstream>
#include "graph.h"
#include "algorithms.hpp"

using namespace std;
using namespace algos;
    
int main() {
    cout << "Building graph..." << endl;
    string dataset = "../web.tsv";
    Graph g(dataset);

    // cout << "The graph's size is " << g.getSize() << endl;

    // std::vector<Graph::Edge*> edges = g.incidentEdges(g.getVertex(0));
    // cout << "The edges connected to the first vertex are: " << endl;
    // for (int i = 0; i < (int)(edges.size()); i++) {
    //     cout << *(edges[i]) << endl;
    // }

    // cout << "Running bfs traversal..." << endl;

    // vector<Vertex> bfs_traversal = bfs(g, g.getVertex(0));

    // cout << "The traversal contains " << bfs_traversal.size() << " vertices." << endl;
    // cout << "The first 50 vertices in the traversal are: " << endl;
    // for (int i = 0; i < 10; i++) {
    //     cout << bfs_traversal.at(i) << " -> ";
    // }
    // cout << endl;

    // cout << "Traversal complete!" << endl;
    // vector<double> vec = pageRank(g, 0.85, 500);

    // for (unsigned long i = 0; i < 5; i++) {
    //     cout << vec.at(i) << " " ;
    // }

    // vector<vector<double>> adjm = g.getAdjM();

    // for (auto row : adjm) {
    //     for (auto col : row) {
    //         cout << col << " ";
    //     }
    //     cout << endl;
    // }

    // vector<vector<int>> indx = g.getIndices();
    // vector<vector<double>> vals = g.getValues();

    // for (auto row : indx) {
    //     for (auto col : row) {
    //         cout << col << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // for (auto row : vals) {
    //     for (auto col : row) {
    //         cout << col << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}

