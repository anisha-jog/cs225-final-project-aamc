#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

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
            Vertex(int idx, int link, int ids) : index(idx), lowlink(link), id(to_string(ids)) { onStack = false; };

            // sorry i'm not following?ok. it should be unique yes
            //build separate class, overload operator () returns size_t takes in vertex.
            //i believe i sawsomething online for that. i just declare it at the top of this file and that's ok right?
            // 
            bool operator==(const Vertex& other) const {
                return id == other.id; 
            }

            bool operator!=(const Vertex& other) const {
                return !(id == other.id);
            }
        };
        // i think i had this error, not with vertex but idk why this even happens
        struct Edge {
            Vertex source;
            Vertex destination;
            double weight;

            Edge() { weight = 1; };
            Edge(Vertex src, Vertex dest) : source(src), destination(dest) { weight = 1; };
            Edge(Vertex src, Vertex dest, double wgt) : source(src), destination(dest), weight(wgt) {};
        };


        struct MyHash {
            std::size_t operator()(const Vertex& v) const {
                std::size_t h1 = std::hash<std::string>{}(v.id);
                return h1;
            }
        };

        Graph();
        Graph(std::ifstream& fs);
        ~Graph();
        Graph(const Graph& other);
        bool operator==(const Graph& other) const;
        vector<Edge*> connectedEdges(Vertex v);
        Vertex getVertex(int i) { return vertices[i]; }
        std::vector<Edge*> getEdges(Vertex v) { return adjacencyList.at(v); }
        void insertVertex(Vertex v);
        void insertEdge(Vertex v1, Vertex v2);
        int getSize() { return vertices.size(); }
        std::vector<Graph::Edge*> incidentEdges(Vertex v) const;

        void clear();

    private:
        std::unordered_map<Vertex, std::vector<Edge*>, MyHash> adjacencyList;
        std::vector<Vertex> vertices;
        std::unordered_map<Vertex, int, MyHash> vertI;
};