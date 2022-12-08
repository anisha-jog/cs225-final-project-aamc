#include "graph.h"

#include <queue>
#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <numeric>

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
    vector<double> pageRank(Graph& graph, double alpha=0.85, int iterations=1000, double tolerance=1e-7) { 
        vector<double> pr_vec;    
        bool done = false;
        int row;
        double sum;

        pr_vec.resize(graph.getIndices().size());
        graph.getPR_Vec().resize(graph.getIndices().size(), 0);
        graph.getPR_Vec()[0] = 1;
        
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

    list<pair<Vertex, double>> pgrank_test(Graph& graph, double alpha=0.85, int iterations=1000, double tolerance=1e-7) {
        // Using the Markov Chains interpretation of PageRank, we will be using the following method:
        // - create a vector x of equal probability, equivalent to the size of our graph
        //   (this vector is the probability set of starting points, i.e. you start at a random site.)
        // - apply the formula alpha * adjM + (1 - alpha) * x
        //   (alpha denotes the probability that a user will click on a link from the page they are currently on.
        //   this formula ensures that no connections are truly 0, as it is possible for a user to get bored and
        //   move to a random page.)
        // - for our number of iterations, compute new graph ^ iterations and multiply with starting vector
        //   (our iterations are indicative of the number of pages the user will visit.)
        //   (we will also make sure we are not hitting tolerance, i.e. if we hit tolerance then it is considered stable.)
        // - sort and return PageRank vector
        list<pair<Vertex, double>> page_list;
        int n = graph.getSize();
        vector<Vertex> vertices = graph.getVertices();
        vector<vector<double>> adjm = graph.getAdjM();

        vector<double> x(n, 1.0 / n);

        // here is where we apply our formula
        for (int i = 0; i < (int)adjm.size(); i++) {
            for (int j = 0; j < (int)adjm[i].size(); j++) {
                adjm[i][j] = alpha * adjm[i][j] + (1-alpha) * x[i];
            }
        }

        vector<double> prev(n);
        double diff = 0; // TODO: calculate Euclidean normalization for diff

        while (diff >= tolerance && iterations > 0) {
            prev = x;
            // TODO: compute the inner product for our graph (G * original G)
            // TODO: recompute diff
            iterations--;
        }

        vector<int> idx(x.size());
        std::iota(idx.begin(), idx.end(), 0);
        stable_sort(idx.begin(), idx.end(), [&x](size_t a, size_t b) {return x[a] > x[b];});

        for(size_t i : idx) {
            page_list.emplace_back(make_pair(vertices[i], x[i]));
        }
        return page_list;
    }
}