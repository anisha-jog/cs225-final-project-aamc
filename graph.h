#pragma once

#include <vector>
#include <string>

using namespace std;

typedef string Vertex;

class Graph {
    public:
        struct Edge {
            Vertex source;
            Vertex destination;
            double weight = 1;

            Edge(){};
            Edge(Vertex src, Vertex dest) : source(src), destination(dest) {};
            Edge(Vertex src, Vertex dest, double wgt) : source(src), destination(dest), weight(wgt) {};
        };

        Graph(){};
        ~Graph();
        Graph(const Graph& other);
        bool operator==(const Graph& other) const;

        void insertVertex(Vertex v);
        void insertEdge(Vertex v1, Vertex v2);

    private:
        
};