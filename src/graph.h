#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

using namespace std;

class Graph {
    public:
        struct Vertex {
            int index;
            int lowlink;
            string id;
            bool onStack;

            Vertex() { index = -1; lowlink = -1; id = -1; onStack = false; };
            Vertex(int ids) : id(to_string(ids)) { index = -1; lowlink = -1; onStack = false; };
            Vertex(string ids) : id(ids) { index = -1; lowlink = -1; onStack = false; };
            Vertex(int idx, int link, int ids) : index(idx), lowlink(link), id(to_string(ids)) { onStack = false; };
            int getID() { return stoi(id); }

            bool operator==(const Vertex& other) const {
                return id == other.id; 
            }

            bool operator==(const int& other) const {
                return id == to_string(other);
            }

            bool operator!=(const Vertex& other) const {
                return !(id == other.id);
            }

            friend ostream& operator<<(ostream& os, const Vertex& v) {
                os << v.id;
                return os;
            }
        };

        struct Edge {
            Vertex source;
            Vertex destination;
            double weight = 1.0;

            Edge() { };
            Edge(Vertex src, Vertex dest) : source(src), destination(dest) { weight = 1; };
            Edge(Vertex src, Vertex dest, double wgt) : source(src), destination(dest), weight(wgt) {};

            friend ostream& operator<<(ostream& os, const Edge& e) {
                // cout << "Edge << called" << endl;
                os << e.source << " -> " << e.destination << " with weight " << e.weight;
                return os;
            }
        };

        struct Hash {
            std::size_t operator()(const Vertex& v) const {
                std::size_t h1 = std::hash<std::string>{}(v.id);
                return h1;
            }
        };

        /**
         * Rule of three functions & helper functions.
        */
        Graph() {};
        Graph(std::ifstream& fs);
        ~Graph();
        bool operator==(const Graph& other) const;
        void clear();

        /**
         * getVertex returns a vertex at the given index.
         * incidentEdges returns a vector of all of the edges leaving a given vertex.
        */
        Vertex getVertex(int i) { return vertices[i]; }
        std::vector<Graph::Vertex> getVertices() { return vertices; }
        vector<Edge*> incidentEdges(Vertex v) const;

        /**
         * Add or remove vertices and edges.
        */
        void insertVertex(Vertex v);
        void insertEdge(Vertex v1, Vertex v2);
        void removeVertex(Vertex v);
        void removeEdge(Vertex v1, Vertex v2);

        /**
         * Determines if two vertices are adjacent to each other.
         * NOTE: determine if our implementation needs this.
        */
        bool areAdjacent(Vertex v1, Vertex v2);

        /**
         * Get the number of vertices of the whole graph.
        */
        int getSize() { return vertices.size(); }

    private:
        /*
         * Variables:
         * - adjacencyList: an unordered map that stores a vertex as a key and all of its edges (pointers) as values.
         * - vertices: a vector containing all of the vertices in the graph.
         * - vertI: an unordered map that stores a vertex as a key and its corresponding index in the vertices vector as a value.
        */
        std::unordered_map<Vertex, std::vector<Edge*>, Hash> adjacencyList;
        std::vector<Vertex> vertices;
        std::unordered_map<Vertex, int, Hash> vertI;
};