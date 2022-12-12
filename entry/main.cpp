#include <iostream>
#include <fstream>
#include "graph.h"
#include "algorithms.hpp"

using namespace std;
using namespace algos;

int main() {
    // NOTE: change path in dataset string to change the input graph file.
    string dataset = "";
    cout << endl << "Input the name of the file you want to build a graph from. Please ensure that this file is in the input folder." << endl;
    cout << "Enter file name: ";
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

    // NOTE: change the number in getVertex() to change the starting vertex.
    cout << "Running bfs traversal..." << endl;
    vector<Vertex> bfs_traversal = bfs(g, g.getVertex(0));
    cout << "Traversal complete!" << endl;

    cout << "The traversal contains " << bfs_traversal.size() << " vertices." << endl;

    // NOTE: to change output file, change the path in bfs_file
    cout << endl << "Input the name of the file you want to write the BFS traversal to. Please ensure that this file is in the output folder." << endl;
    cout << "Enter file name: ";
    string bfs_file = "";
    cin >> bfs_file;
    cout << "Writing BFS traversal to file..." << endl;
    BFSWriteToFile(bfs_traversal, "../output/" + bfs_file);
    cout << "Traversal written to " << bfs_file << endl << endl;

    // NOTE: change the third number in the pagerank function (num iterations) to change the iterations of the PageRank algorithm.
    // Lower numbers are recommended for low-performance computers.
    // Change the second number to change the alpha value and see how it affects the algorithm.
    cout << "Running PageRank..." << endl;
    vector<pair<Vertex, double>> vec = pageRank(g, 0.5, 5);
    cout << "The PageRank vector is " << vec.size() << " pages long." << endl;
    
    // NOTE: to change output file, change the path in pgrank_file
    cout << endl << "Input the name of the file you want to write the PageRank vector to. Please ensure that this file is in the output folder." << endl;
    cout << "Enter file name: ";
    string pgrank_file = "";
    cin >> pgrank_file;
    cout << "Writing PageRank list to file..." << endl;
    PageRankWriteToFile(vec, "../output/" + pgrank_file);
    cout << "PageRank list written to " << pgrank_file << endl << endl;
   
    return 0;
}

