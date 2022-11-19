#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

typedef string Vertex;

class Graph {
    public:
        struct Edge {
            Vertex source;
            Vertex destination;
            double weight = 1;

            Edge() {};
            Edge(Vertex src, Vertex dest) : source(src), destination(dest) {};
            Edge(Vertex src, Vertex dest, double wgt) : source(src), destination(dest), weight(wgt) {};
        };

        Graph() {};
        Graph(std::ifstream& fs);
        ~Graph();
        Graph(const Graph& other);
        bool operator==(const Graph& other) const;
        vector<Edge*> connectedEdges(Vertex v);
        Vertex getVertex(int i) { return vertices[i]; }
        void insertVertex(Vertex v);
        void insertEdge(Vertex v1, Vertex v2);
        int getSize() { return vertices.size(); }
        std::vector<Graph::Edge*> incidentEdges(Vertex v) const;

        void clear();

    private:
        std::unordered_map<Vertex, std::vector<Edge*>> adjacencyList;
        std::vector<Vertex> vertices;
        std::unordered_map<Vertex, int> vertI;
};