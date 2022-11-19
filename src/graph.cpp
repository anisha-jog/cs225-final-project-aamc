#include "graph.h"

Graph::~Graph() {
    clear();
}

void Graph::clear() {
    vertI.clear();
    vertices.clear();

    for (std::pair<Vertex, std::vector<Graph::Edge *>> child : adjacencyList) {
        for (unsigned i = 0; i < child.second.size(); i++) if (child.second[i]) delete child.second[i];
    }
}

Graph::Graph(const Graph& other) {
    unsigned size = other.adjacencyList.size();
    std::vector<Edge *> temp;

    for (auto entry : other.adjacencyList) {
        temp.clear();
        for (Edge * edge : entry.second) {
            temp.push_back(new Graph::Edge(edge->source, edge->destination));
        }
        this->adjacencyList.insert(std::make_pair(entry.first, temp));
    }

    for (unsigned i = 0; i < size; i++) {
        this->vertices.push_back(other.vertices[i]);
    }

    for (auto entry : vertI) {
        this->vertI.insert(std::make_pair(entry.first, entry.second));
    }
}

bool Graph::operator==(const Graph& other) const {
    unsigned size = other.adjacencyList.size();
    
    if (this->adjacencyList.size() != size) return false;

    for (auto entry : other.adjacencyList) {
        auto thisl = this->adjacencyList.at(entry.first);
        if (thisl.size() != entry.second.size()) return false;
        for (unsigned i = 0; i < entry.second.size(); i++) {
            if (entry.second[i]->source != thisl[i]->source 
                || entry.second[i]->destination != thisl[i]->destination) return false;
        }
    }

    return true;
}

// Creating the adjacency list
Graph::Graph(std::ifstream& fs) {
    Vertex v1, v2;
    while (!fs.eof()) {
        getline(fs, v1.id, '\t');
        getline(fs, v2.id, '\n');
        
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

void Graph::insertVertex(Vertex v) {
    vertI[v] = vertI.size();
    vertices.push_back(v);
    adjacencyList[v] = std::vector<Edge *>();
}

void Graph::insertEdge(Vertex v1, Vertex v2) {
    std::vector<Edge*> & edges = adjacencyList[v1];
    edges.insert(edges.begin(), new Edge(v1, v2));
}

std::vector<Graph::Edge*> Graph::incidentEdges(Vertex v) const {
    std::vector<Graph::Edge*> incidentEdges = adjacencyList.at(v);
    return incidentEdges;
}