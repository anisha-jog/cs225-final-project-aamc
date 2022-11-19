#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

class Graph {
    public:
        struct Edge {
            Vertex source;
            Vertex destination;
            double weight;

            Edge() { weight = 1; };
            Edge(Vertex src, Vertex dest) : source(src), destination(dest) { weight = 1; };
            Edge(Vertex src, Vertex dest, double wgt) : source(src), destination(dest), weight(wgt) {};
        };

        struct Vertex {
            int index;
            int lowlink;
            string id;
            bool onStack;

            Vertex() { index = -1; lowlink = -1; id = -1; onStack = false; };
            Vertex(int ids) : id(to_string(ids)) { index = -1; lowlink = -1; onStack = false; };
            Vertex(int idx, int link, int ids) : index(idx), lowlink(link), id(to_string(ids)) { onStack = false; };
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