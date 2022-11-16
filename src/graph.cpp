#include "graph.h"

Graph::~Graph() {

}

Graph::Graph(const Graph& other) {

}

bool Graph::operator==(const Graph& other) const {
    return false;
}

// Creating the adjacency list
Graph::Graph(std::ifstream& fs) {
    Vertex v1, v2;
    while (!fs.eof()) {
        getline(fs, v1, '\t');
        getline(fs, v2, '\n');
        
        if (vertI.find(v1) == vertI.end()) { 
            vertI[v1] = vertI.size();
            vertices.push_back(v1);
        }

        adjacencyList[v1].push_back(new Graph::Edge(v1, v2));
        
        if (adjacencyList.find(v2) == adjacencyList.end()) { 
            adjacencyList[v2] = std::vector<Graph::Edge*>();
            vertI.insert(std::make_pair(v2, vertI.size()));
            vertices.push_back(v2);
        }
    }
}