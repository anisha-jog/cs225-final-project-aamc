#include "graph.h"

#include <queue>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <cstdio>
#include <cstdlib>

using namespace std;
using Edge = Graph::Edge;
using Vertex = Graph::Vertex;


namespace algos {

    struct Hash {
        std::size_t operator()(const Vertex v) const {
            std::size_t h1 = std::hash<std::string>{}(v.id);
            return h1;
        }
    };

    /**
     * BREADTH FIRST SEARCH ALGORITHM
     **/
    vector<Vertex> bfs(Graph graph, Vertex start) {
        unordered_map<Vertex, int, Hash> visited;
        vector<Vertex> traversal;
        queue<Vertex> q;

        // add start point to the queue
        visited[start] = 1;
        traversal.push_back(start);
        q.push(start);
        
        while(!q.empty()) {
            // get all the edges that are connected to the first vertex and then pop it from the queue
            vector<Edge*> connections = graph.incidentEdges(q.front());
            q.pop();

            // loop through each connection of the vertex
            for (int i = 0; i < (int)(connections.size()); i++) {
                // if the destination of the edge (connected vertex) isn't in the visited map, add it
                if (visited.find(connections[i]->destination) == visited.end()) {
                    // cout << "destination not in visited map" << endl;
                    // it goes next in the traversal, add it to the queue, and mark it in the visited map
                    traversal.push_back(connections[i]->destination);
                    q.push(connections[i]->destination);
                    visited[connections[i]->destination] = 1;
                }
            }
        }

        // go through the rest of the graph
        for (int i = 0; i < (int)graph.getSize(); i++) {
            // for any vertex that hasn't been visited yet, add it to the queue and go again
            // takes care of the groups that aren't connected to the start point
            if (visited.find(graph.getVertex(i)) == visited.end()) {
                // cout << "vertex has not been visited yet" << endl;
                q.push(graph.getVertex(i));
                visited[graph.getVertex(i)] = 1;
                traversal.push_back(graph.getVertex(i));

                while(!q.empty()) {
                    std::vector<Edge*> connections = graph.incidentEdges(q.front());
                    q.pop();
                
                    for (int i = 0; i < int(connections.size()); i++) {
                        if (visited.find(connections[i]->destination) == visited.end()) {
                            // cout << "destination has not been visited yet" << endl;
                            traversal.push_back(connections[i]->destination);
                            q.push(connections[i]->destination);
                            visited[connections[i]->destination] = 1;
                        }
                    }
                }  
            }
        }
        // by this point, every vertex has been in the queue, popped, visited, and added to the traversal.

        return traversal;
    }


    // Setup PageRank Algorithm
    // https://www.ccs.neu.edu/home/daikeshi/notes/PageRank.pdf
    vector<double> pageRank(Graph& graph,  double alpha=0.85, int iterations=1000, double tolerance=1e-7) { 
        vector<double> pr_vec;    
        bool done = false;
        int row;
        double sum;

        pr_vec.resize(graph.getIndices().size());
        graph.getPR_Vec().resize(graph.getIndices().size(), 0);
        graph.getPR_Vec()[0] = 1;

        graph.adjacencyMatrix();
        
        while (!done) {
    
            // Calculating the sum of pr values for all of the nodes with no edge coming out of their adjacency lists

            sum = 0;
            for (unsigned long i = 0; i < graph.getAdjList().size(); i++) {
                if (graph.getAdjList()[i].size() == 0) sum += graph.getPR_Vec()[i];
            }
            
            sum /= (double) graph.getPR_Vec().size();

            pr_vec.clear();
            pr_vec.resize(graph.getPR_Vec().size(), sum);

            for (unsigned long i = 0; i < graph.getPR_Vec().size(); i++) {
                // Calculating the new values of pr_vec
                sum = 0;
                for (unsigned long j = 0; j < graph.getIndices()[i].size(); j++) {
                    row = graph.getIndices()[i][j];
                    sum += graph.getValues()[i][j] * graph.getPR_Vec()[row];
                }
                pr_vec[i] += sum;
            }

            // See if the new and old values are close enough to quit.
            done = true;                
            for (unsigned long i = 0; done && i < graph.getPR_Vec().size(); i++) {
                if (graph.getPR_Vec()[i] - pr_vec[i] > tolerance || pr_vec[i] - graph.getPR_Vec()[i] > tolerance) done = false;
            }
            graph.getPR_Vec() = pr_vec; 
        }

        return graph.getPR_Vec();
    }

    // Helper function for Tarjan's Algorithm
    void strongConnect(Graph graph, Vertex v, std::stack<Vertex>& stack, int idx) {
        v.index = idx;
        v.lowlink = idx;
        idx++;
        stack.push(v);
        v.onStack = true;
        std::vector<Edge*> edges = graph.incidentEdges(v);

        // Consider the successors of v.
        for (int j = 0; j < (int)(edges.size()); j++) {
            Vertex dest = edges[j]->destination;
            if (dest.index == -1) {
                // Vertex has not been visited; recurse.
                strongConnect(graph, dest, stack, idx);
                if (dest.lowlink < v.lowlink) {
                    v.lowlink = dest.lowlink;
                }
            } else if (dest.onStack) {
                // Vertex is already in stack, and therefore has been visited. Index, rather, than lowlink, is not a mistake.
                if (dest.index < v.lowlink) {
                    v.lowlink = dest.index;
                }
            }
        }

        // Check if v is a root node
        if (v.lowlink == v.index) {

            // TODO: Create a new strongly connected component

            // - - - -

            Vertex pop;
            
            while (pop != v) {
                pop = stack.top();
                stack.pop();
                pop.onStack = false;

                // TODO: Add vertex to strongly connected component

                // - - - -

            }

            // Output strongly connected component

            // - - - -

        }
    }

    // Tarjan's Algorithm
    vector<Vertex> tarjan(Graph graph) {
        int idx = 0;
        std::stack<Vertex> stack;

        for (int i = 0; i < graph.getSize(); i++) {
            if (graph.getVertex(i).index == -1) {
                strongConnect(graph, graph.getVertex(i), stack, idx);
            }
        }

        return vector<Vertex>();
    }
}