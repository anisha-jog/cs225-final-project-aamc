#include <iostream>
#include <fstream>
#include "graph.h"
#include "algorithms.hpp"

using namespace std;
using namespace algos;

int main() {
    // NOTE: change path in dataset string to change the input graph file.
    string dataset = "";
    cout << "Input the name of the file you want to read from. Please ensure that this file is in the input folder." << endl;
    cin >> dataset;

    if (dataset == "") {
        cout << "Sorry, we can't build a graph without an input!" << endl;
        return 0;
    }

    cout << "Building graph..." << endl;
    // NOTE: change the number to change the maximum number of nodes.
    // Add in a third argument to change the number of lines you want to read from file.
    // Lower numbers are recommended for low-performance computers.
    Graph g("../input/" + dataset, 10000);

    cout << "The graph's size is " << g.getSize() << endl;

    // std::vector<Graph::Edge*> edges = g.incidentEdges(g.getVertex(0));
    // cout << "The edges connected to the first vertex are: " << endl;
    // for (int i = 0; i < (int)(edges.size()); i++) {
    //     cout << *(edges[i]) << endl;
    // }

    // NOTE: change the number in getVertex() to change the starting vertex.
    cout << "Running bfs traversal..." << endl;
    vector<Vertex> bfs_traversal = bfs(g, g.getVertex(0));
    cout << "Traversal complete!" << endl;

    cout << "The traversal contains " << bfs_traversal.size() << " vertices." << endl;
    // cout << "The first 10 vertices in the traversal are: " << endl;
    // for (int i = 0; i < 9; i++) {
    //     cout << bfs_traversal.at(i) << " -> ";
    // }
    // cout << bfs_traversal.at(bfs_traversal.size()-1) << endl;

    // NOTE: to change output file, change the path in bfs_file
    cout << "Input the name of the file you want to write the BFS traversal to. Please ensure that this file is in the output folder." << endl;
    string bfs_file = "";
    cin >> bfs_file;
    cout << "Writing BFS traversal to file..." << endl;
    BFSWriteToFile(bfs_traversal, "../output/" + bfs_file);
    cout << "Traversal written to " << bfs_file << endl << endl;

    std::unordered_map<Vertex, std::vector<Edge*>, Graph::Hash> adjlist = g.getAdjList();

    for (auto v : adjlist) {
        cout << v.first << ": " << endl;
        for (auto edge : adjlist[v.first]) {
            cout << (*edge) << endl;
        }
    }
    cout << endl;

    vector<vector<double>> adj = g.getAdjM();
    for (int i = 0; i < (int)adj.size(); i++) {
        for (int j = 0; j < (int)adj[i].size(); j++) {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // NOTE: change the third number in the pagerank function (num iterations) to change the iterations of the PageRank algorithm.
    // Lower numbers are recommended for low-performance computers.
    // Change the second number to change the alpha value and see how it affects the algorithm.
    cout << "Running PageRank..." << endl;
    vector<pair<Vertex, double>> vec = pageRank(g, 0.85, 10);
    cout << "The PageRank vector is " << vec.size() << " pages long." << endl;

    for (unsigned long i = 0; i < vec.size(); i++) {
        cout << vec[i].first << " " << vec[i].second << endl;
    }
    
    // NOTE: to change output file, change the path in pgrank_file
    cout << "Input the name of the file you want to write the PageRank vector to. Please ensure that this file is in the output folder." << endl;
    string pgrank_file = "";
    cin >> pgrank_file;
    cout << "Writing PageRank list to file..." << endl;
    PageRankWriteToFile(vec, "../output/" + pgrank_file);
    cout << "PageRank list written to " << pgrank_file << endl << endl;
   
    return 0;
}

