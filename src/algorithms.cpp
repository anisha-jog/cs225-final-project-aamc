#include "graph.h"

#include <queue>
#include <vector>

using namespace std;
using Edge = Graph::Edge;

vector<Vertex> bfs(Graph graph, Vertex start) {
    unordered_map<Vertex, int> visited;
    vector<Vertex> traversal;
    queue<Vertex> q;

    // add start point to the queue
    visited[start] = 1;
    traversal.push_back(start);
    q.push(start);
    
    while(!q.empty()) {
        // get all the edges that are connected to the first vertex and then pop it from the queue
        vector<Edge*> connections = graph.connectedEdges(q.front());
        q.pop();

        // loop through each connection of the vertex
        for (int i = 0; i < (int)(connections.size()); i++) {
            // if the destination of the edge (connected vertex) isn't in the visited map, add it
            if (visited.find(connections[i]->destination) == visited.end()) {
                // it goes next in the traversal, add it to the queue, and mark it in the visited map
                traversal.push_back(connections[i]->destination);
                q.push(connections[i]->destination);
                visited[connections[i]->destination] = 1;
            }
        }
    }

    // go through the rest of the graph
    for (int i = 0; i < graph.getSize(); i++) {
        // for any vertex that hasn't been visited yet, add it to the queue and go again
        // takes care of the groups that aren't connected to the start point
        if (visited.find(graph.getVertex(i)) == visited.end()) {
            q.push(graph.getVertex(i));
            visited[graph.getVertex(i)] = 1;
            traversal.push_back(graph.getVertex(i));

            while(!q.empty()) {
                std::vector<Edge*> connections = graph.connectedEdges(q.front());
                q.pop();
            
                for (int i = 0; i < int(connections.size()); i++) {
                    if (visited.find(connections[i]->destination) == visited.end()) {
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