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
            string id;
            bool onStack;

            Vertex() { id = -1; };
            Vertex(int ids) : id(to_string(ids)) {};
            Vertex(string ids) : id(ids) {};
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
        Graph(string filename);
        ~Graph();
        Graph(const Graph &other);
        Graph & operator=(const Graph & other);
        bool operator==(const Graph& other) const;
        void clear();

        /**
         * getVertex returns a vertex at the given index.
         * incidentEdges returns a vector of all of the edges leaving a given vertex.
         * Helper functions to access member variables in algos namespace.
        */
        Vertex getVertex(int i) { return vertices[i]; }
        vector<Edge*> incidentEdges(Vertex v) const;
        std::vector<Graph::Vertex> getVertices() { return vertices; }
        std::unordered_map<Vertex, std::vector<Edge*>, Hash> getAdjList() { return adjacencyList; }

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

        /**
         * Creates the adjacency matrix.
         * Helper functions to access member variables in algos namespace.
        */
        void createAdjM();
        void adjMatInd();
        vector<vector<double>> getAdjM() { return adjacencyMatrix; }
        vector<vector<int>> getIndices() { return indices; }
        vector<vector<double>> getValues() { return values; }
        vector<double> getPR_Vec() { return pr_vec; }

    private:
        /*
         * Variables:
         * - adjacencyList: An unordered map that stores a vertex as a key and all of its edges (pointers) as values.
         * - vertices: A vector containing all of the vertices in the graph.
         * - vertI: An unordered map that stores a vertex as a key and its corresponding index in the vertices vector as a value.
         * 
         * PageRank specific variables:
         * indices: Sparse representation of matrix indices
         * values: Sparse representation of matrix values
         * pr_vec: The pagerank vector
        */
        std::unordered_map<Vertex, std::vector<Edge*>, Hash> adjacencyList;
        vector<vector<double>> adjacencyMatrix;
        std::vector<Vertex> vertices;
        std::unordered_map<Vertex, int, Hash> vertI;

        vector<vector<int>> indices;
        vector<vector<double>> values;
        vector<double> pr_vec;
};