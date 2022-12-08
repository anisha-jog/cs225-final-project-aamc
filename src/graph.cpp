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
    // 
    vertI.clear();
    vertices.clear();

    for (std::pair<Vertex, vector<Edge*>> child : adjacencyList) {
        // TODO: this is segfaulting, figure out why
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

Graph::Graph(std::ifstream& fs) {
    // Reading the data from a file and populating the adjacency list
    Vertex v1, v2;
    while (!fs.eof()) {
        string x, y;
        getline(fs, v1.id, '\t');
        getline(fs, v2.id, '\n');
        
        if (vertI.find(v1) == vertI.end()) { 
            vertI[v1] = vertI.size();
            vertices.push_back(v1);
        }


        adjacencyList[v1].push_back(new Graph::Edge(v1, v2));

        
        if (adjacencyList.find(v2) == adjacencyList.end()) { 
            adjacencyList[v2] = vector<Edge*>();
            vertI.insert(std::make_pair(v2, vertI.size()));
            vertices.push_back(v2);
        }
        // if (v1.id > "5" || v2.id > "5") {
        //     continue;
        // }
    }
    
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

void Graph::adjacencyMatrix() {
    // Making the adjacency matrix from the adjacency list

    double x;

    indices.resize(adjacencyList.size());
    values.resize(adjacencyList.size());

    for (unsigned long i = 0; i < adjacencyList.size(); i++) {
        if (adjacencyList[i].size() != 0) {
            x = 1 / (double) adjacencyList[i].size();
            for (unsigned long j = 0; j < adjacencyList.at(i).size(); j++) {
                int ind = system(adjacencyList.at(i).at(j)->source.id.c_str());
                indices.at(ind).push_back(i);
                values.at(ind).push_back(x);
            }
        }
    }
}