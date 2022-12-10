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

Graph::Graph(string filename, int cap) {
    // Reading the data from a file and populating the adjacency list
    Vertex v1, v2;
    ifstream fs;
    fs.open(filename);
    if (fs.is_open()) {
        cout << "File opened successfully." << endl;
    } else {
        cout << "Error opening file." << endl;
        return;
    }
    while (!fs.eof()) {
        // string x, y;
        fs >> v1.id;
        fs >> v2.id;
        // std::getline(fs, x, '\t');
        // std::getline(fs, y, '\n');
        // cout << "Reading: " << x << " -> " << y << endl;

        // scales down the dataset
        if (v1.getID() > cap || v2.getID() > cap) continue;
        
        if (vertI.find(v1) == vertI.end()) { 
            vertI[v1] = vertI.size();
            vertices.push_back(v1);
        }

        adjacencyList[v1].push_back(new Graph::Edge(v1, v2));

        if (adjacencyList.find(v2) == adjacencyList.end()) {
            // cout << "vertex not in adjacency list" << endl;
            adjacencyList[v2] = vector<Edge*>();
            vertI.insert(std::make_pair(v2, vertI.size()));
            vertices.push_back(v2);
        }
    }

    cout << "file read" << endl;
    fs.close();
    createAdjM();
    // sparseAdjacencyMatrix();
    cout << "matrix created" << endl;
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

void Graph::removeVertex(Vertex v) {
    // TODO: remove the vertex from all lists and delete data accordingly
}

void Graph::removeEdge(Vertex v1, Vertex v2) {
    // TODO: remove the edge from the adjacency list and delete data accordingly
}

bool Graph::areAdjacent(Vertex v1, Vertex v2) {
    // TODO - see note in graph.h.
    return false;
}

void Graph::createAdjM() {
    // Making the adjacency matrix from the adjacency list
    // cout << "making adjm" << endl;

    // resize the adjacency matrix
    int dim = adjacencyList.size();
    adjacencyMatrix.resize(dim);
    for (int i = 0; i < dim; i++) {
        adjacencyMatrix[i].resize(dim);
    }
    // cout << "matrix resized" << endl;

    // initialize adjacency using our adjacency list
    for(auto entry : adjacencyList) {
        auto edges = entry.second;
        int col = vertI[entry.first];
        if(edges.size()) { // if it has edges
            double val = 1.0/edges.size();
            // cout << "populizing col with connection weights" << endl;
            for(auto edge : edges) {
                adjacencyMatrix[vertI[edge->destination]][col] = val;
            }
        } else {
            // cout << "populizing col generally" << endl;
            double val = 1.0/adjacencyList.size();
            for(size_t row = 0; row < adjacencyList.size(); row++) {
                adjacencyMatrix[row][col] = val;
            }
        }
    }
}

bool Graph::CSR(vector<vector<double>> matrix) {

    for (int i = 0; i < (int)matrix.size(); i++) {
        for (int j = 0; j < (int)matrix[i].size(); j++) {
            if (matrix[i][j] != 0) {
                row.push_back(i);
                col.push_back(j);
                values.push_back(matrix[i][j]);
            }
        }
    }
    return true;
}

void Graph::matrixMult(vector<int> r1, vector<int> c1, vector<double> v1, vector<int> r2, vector<int> c2, vector<double> v2) {
    vector<int> new_r, new_c;
    vector<double> new_v;
    for (unsigned long i = 0; i < r1.size() && i < r2.size(); i++) {
        for (unsigned long j = 0; j < c1.size() && j < c2.size(); j++) {
            if (r1[i] == r2[i] && c1[j] == c2[j]) {
                new_r.push_back(r1[i]);
                new_c.push_back(c1[j]);
                new_v.push_back(r1[i] * c1[j]);
            }
        }
    }
    row = new_r;
    col = new_c;
    values = new_v;
}
