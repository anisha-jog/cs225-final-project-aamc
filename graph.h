#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;
//ok we cant do rule of 0 bc we have to deal with memory dumbass
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

            bool operator!=(Vertex& other) {
                return index != other.index && lowlink != other.lowlink && id != other.id && onStack != other.onStack;
            }
        };
        
        struct Edge {
            Vertex source;
            Vertex destination;
            double weight = 1.0;

            Edge() { };
            Edge(Vertex src, Vertex dest) : source(src), destination(dest) { weight = 1; };
            Edge(Vertex src, Vertex dest, double wgt) : source(src), destination(dest), weight(wgt) {};
        };

        Graph();
        Graph(std::ifstream& fs);
        bool operator==(const Graph& other) const;
        vector<Edge*> connectedEdges(Vertex v);
        Vertex getVertex(int i) { return vertices[i]; }
        std::vector<Edge*> getEdges(Vertex v) { return adjacencyList.at(v); }
        void insertVertex(Vertex v);
        void insertEdge(Vertex v1, Vertex v2);
        int getSize() { return vertices.size(); }
        std::vector<Graph::Edge*> incidentEdges(Vertex v) const;

        void clear();


        /**
         * Member variables
         * adjacencyList: unordered_map storing the vertex as a key, and a list of outgoing edge pointers as the value
         * adjacencyMatrix: normalized boost::ublas matrix keeping track of outgoing edges; used for areAdjacent & pageRank algorithm
         * vertexList: a list of all vertices, in order they are added to the adjacencyList
         * vert_to_ind: unordered_map that stores a vertex as the key, and its associated index in vertexList as the value
         */
        
        unordered_map<Vertex, std::vector<Edge*>> adjacencyList;
        vector<Vertex> vertices;
        unordered_map<Vertex, int> vertI;
};