#include <iostream>
#include <string>
// Read file and create adjacency list
#include "algorithms.hpp"
#include "graph.h"
    
int main() {
    ifstream dataset("web-Google.txt");
    Graph defaultGraph(dataset);
    // string dataread;
    // if (dataset.is_open()) {
    //     dataset >> dataread;
    //     cout << dataread << endl;
    // }
    std::string defaultMessage = "Default Algorithm Results: ";

    std::list<std::pair<Vertex, double>> result_PR = Algos::pageRank(defaultGraph, 0.85, 1000, 1e-7);

    defaultMessage += "\n\n\tPagerank Algorithm for Wikipedia Dataset(http://snap.stanford.edu/data/wikispeedia.html):\n";
    unsigned top_articles = 20;
    for(std::pair<Vertex, double> entry : result_PR) {
        defaultMessage += std::to_string(entry.second * 100) + "%\n";
        if (!--top_articles) break;
    }

    // Printing to File
    std::ofstream out("Outputs/defaultOutput.txt");
    out << defaultMessage;
    out.close();
    return 1;
    return 0;
}