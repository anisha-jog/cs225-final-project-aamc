#include "graph.h"

using Edge = Graph::Edge;
using Vertex = Graph::Vertex;
using namespace std;

Graph::~Graph() {
    // Destructor
    clear();
}

Graph::Graph(const Graph& other) {
    // Copy constructor
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

void Graph::clear() {
    // helper function for the destructor
    vertI.clear();
    vertices.clear();

    for (std::pair<Vertex, vector<Edge*>> child : adjacencyList) {
        for (int i = 0; i < (int)(child.second.size()); i++) delete child.second[i];
    }
}

Graph & Graph::operator=(const Graph & other) {
    if (*this == other) return *this;
    this->clear();
    *this = Graph(other);
    return *this;
}

bool Graph::operator==(const Graph& other) const {
    unsigned size = other.adjacencyList.size();
    
    if (this->adjacencyList.size() != size) return false;

    for (auto entry : other.adjacencyList) { 
        auto thisl = this->adjacencyList.at(entry.first);
        if (thisl.size() != entry.second.size()) return false;
        for (unsigned i = 0; i < entry.second.size(); i++) {
            if (entry.second.at(i)->source != thisl.at(i)->source 
                || entry.second.at(i)->destination != thisl.at(i)->destination) return false;
        }
    }

    return true;
}

Graph::Graph(string filename, int cap, int lines) {
    // Reading the data from a file and populating the adjacency list
    Vertex v1, v2;
    ifstream fs;
    fs.open(filename);
    int l = 0;

    if (fs.is_open()) {
        cout << "File opened successfully." << endl;
    } else {
        cout << "Error opening file." << endl;
        return;
    }

    while (!fs.eof()) {
        // graph size limiter
        if (lines >= 0 && l >= lines) break;

        fs >> v1.id;
        fs >> v2.id;
        l++;

        // graph size limiter
        if (v1.getID() > cap || v2.getID() > cap) continue;
        
        // add first vertex to list if not found
        if (vertI.find(v1) == vertI.end()) { 
            vertI[v1] = vertI.size();
            vertices.push_back(v1);
        }

        // add edge to adjacency list
        adjacencyList[v1].push_back(new Graph::Edge(v1, v2));

        // add second vertex if not found
        if (adjacencyList.find(v2) == adjacencyList.end()) {
            adjacencyList[v2] = vector<Edge*>();
            vertI.insert(std::make_pair(v2, vertI.size()));
            vertices.push_back(v2);
        }
    }

    cout << "File read" << endl;
    fs.close();
}

void Graph::insertVertex(Vertex v) {
    // Inserting a vertex
    vertI[v] = vertI.size();
    vertices.push_back(v);
    adjacencyList[v] = std::vector<Edge *>();
}

void Graph::insertEdge(Vertex v1, Vertex v2) {
    // Inserting an edge
    std::vector<Edge*> & edges = adjacencyList[v1];
    edges.insert(edges.begin(), new Edge(v1, v2));
}

vector<Edge*> Graph::incidentEdges(Vertex v) const {
    // Copying the edge vector
    vector<Edge*> edges = adjacencyList.at(v);
    return edges;
}

void Graph::createAdjM() {
    // resize the adjacency matrix
    int dim = adjacencyList.size();
    adjacencyMatrix.resize(dim);
    for (int i = 0; i < dim; i++) {
        adjacencyMatrix[i].resize(dim);
    }

    // initialize adjacency using our adjacency list
    for(auto entry : adjacencyList) {
        auto edges = entry.second;
        int col = vertI[entry.first];
        if(edges.size() > 0) { // if it has outgoing edges
            double val = 1.0/edges.size();
            for(auto edge : edges) {
                adjacencyMatrix[vertI[edge->destination]][col] = val;
            }
        } else { // if no outgoing edges, all the vertices have the same importance
            double val = 1.0/adjacencyList.size();
            for(size_t row = 0; row < adjacencyList.size(); row++) {
                adjacencyMatrix[row][col] = val;
            }
        }
    }
}