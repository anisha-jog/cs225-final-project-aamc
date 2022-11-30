#include "graph.h"

using Edge = Graph::Edge;
using Vertex = Graph::Vertex;
using namespace std;

Graph::~Graph() {
    clear();
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

void Graph::clear() {
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
    while (!fs.eof()) {
        cout << "reading from file" << endl;
        string x, y;
        // stringstream str()
        getline(fs, x, '\t');
        getline(fs, y, '\n');
        cout << x << " " << y << endl;
        Vertex v1(x), v2(y);
        
        if (vertI.find(v1) == vertI.end()) { 
            cout << "vertex not found" << endl;
            vertI[v1] = vertI.size();
            vertices.push_back(v1);
        }

        cout << "adding to adjacency list: " << v1 << " " << v2 << endl;

        adjacencyList[v1].push_back(new Graph::Edge(v1, v2));

        cout << "added to adjacency list" << endl;
        
        if (adjacencyList.find(v2) == adjacencyList.end()) { 
            cout << "vertex not in adjacency list" << endl;
            adjacencyList[v2] = vector<Edge*>();
            vertI.insert(std::make_pair(v2, vertI.size())); // essentially the same as vertI[v2] = vertI.size()?
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

vector<Edge*> Graph::incidentEdges(Vertex v) const {
    // copying the edge vector?
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
