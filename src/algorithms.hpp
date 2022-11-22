#include "graph.h"

#include <queue>
#include <vector>
#include <list>
#include <stack>

using namespace std;
using Edge = Graph::Edge;
using Vertex = Graph::Vertex;


namespace Algos {

    /**
     * BREADTH FIRST SEARCH ALGORITHM
     **/
    vector<Vertex*> bfs(Graph graph, Vertex *start) {
        unordered_map<Vertex*, int> visited;
        vector<Vertex*> traversal;
        queue<Vertex*> q;

        // add start point to the queue
        visited[start] = 1;
        traversal.push_back(start);
        q.push(start);
        
        while(!q.empty()) {
            // get all the edges that are connected to the first vertex and then pop it from the queue
            vector<Edge*> connections = graph.connectedEdges(*q.front());
            q.pop();

            // loop through each connection of the vertex
            for (int i = 0; i < (int)(connections.size()); i++) {
                // if the destination of the edge (connected vertex) isn't in the visited map, add it
                if (visited.find(&connections[i]->destination) == visited.end()) {
                    // it goes next in the traversal, add it to the queue, and mark it in the visited map
                    traversal.push_back(&connections[i]->destination);
                    q.push(&connections[i]->destination);
                    visited[&connections[i]->destination] = 1;
                }
            }
        }

        // go through the rest of the graph
        for (int i = 0; i < (int)graph.getSize(); i++) {
            // for any vertex that hasn't been visited yet, add it to the queue and go again
            // takes care of the groups that aren't connected to the start point
            if (visited.find(&graph.getVertex(i)) == visited.end()) {
                q.push(&graph.getVertex(i));
                visited.at(&graph.getVertex(i)) = 1;
                traversal.push_back(&graph.getVertex(i));

                while(!q.empty()) {
                    std::vector<Edge*> connections = graph.connectedEdges(*q.front());
                    q.pop();
                
                    for (int i = 0; i < int(connections.size()); i++) {
                        if (visited.find(&connections[i]->destination) == visited.end()) {
                            traversal.push_back(&connections[i]->destination);
                            q.push(&connections[i]->destination);
                            visited[&connections[i]->destination] = 1;
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
    std::list<std::pair<Vertex, double>> pageRank(const Graph& graph,  double alpha=0.85, int iterations=1000, double tolerance=1e-7) { 
        return std::list<std::pair<Vertex, double>>();
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
    }

    // Helper function for Tarjan's Algorithm
    void strongConnect(Graph graph, Vertex v, std::stack<Vertex>& stack, int idx) {
        v.index = idx;
        v.lowlink = idx;
        idx++;
        stack.push(v);
        v.onStack = true;
        std::vector<Edge*> edges = graph.getEdges(v);

        // Consider the successors of v.
        for (int j = 0; j < edges.size(); j++) {
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
}