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
     * @param graph: graph to perform the traversal on
     * @param start: vertex to start at
     * @return A vector of vertices in the traversal order.
     **/
    vector<Vertex> bfs(Graph graph, Vertex start) {
        unordered_map<Vertex, int, Hash> visited;
        vector<Vertex> traversal;
        queue<Vertex> q;

        if (graph.getSize() == 0) {
            cout << "Error: The graph contains no vertices." << endl;
            return traversal;
        }

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

    /**
     * Helper function for multiplying matrices in PageRank.
     * @param graph: graph the algorithm is operating on
     * @param mat1: first 2D matrix to multiply
     * @param mat2: second 2D matrix to multiply
     * @return 2D matrix product.
    */
    vector<vector<double>> multiplyMatrices(Graph& graph, vector<vector<double>> mat1, vector<vector<double>> mat2) {
        // create the product matrix size
        vector<vector<double>> result;
        cout << "Creating results matrix..." << endl;
        for (int i = 0; i < (int)mat1.size(); i++) {
            vector<double> m(mat2[0].size());
            result.push_back(m);
        }
    
        cout << "Calculating product..." << endl;
        for (int i = 0; i < (int)mat1.size(); i++) {
            for (int j = 0; j < (int)mat2[0].size(); j++) {
                result[i][j] = 0;
                for (int k = 0; k < (int)mat1[i].size(); k++) {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
        return result;
    }

    /**
     * Function to write the PageRank vector to a file. Follows https://www.ccs.neu.edu/home/daikeshi/notes/PageRank.pdf
     * @param graph: graph to perform PageRank on
     * @param alpha: parameter determining percentage of randomness
     * @param iterations: number of iterations to run the PageRank algorithm
     * @return A vector of pairs containing a vertex and its PageRank value in descending order.
    */
    vector<pair<Vertex, double>> pageRank(Graph& graph, double alpha=0.85, int iterations=10) {
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

        vector<pair<Vertex, double>> page_list;
        int n = graph.getSize();

        if (n == 0) {
            cout << "Error: The graph contains no vertices." << endl;
            return page_list;
        }

        cout << "Creating adjacency matrix..." << endl;
        graph.createAdjM();
        vector<Vertex> vertices = graph.getVertices();
        vector<vector<double>> adjm = graph.getAdjM();

        vector<double> x(n, 1.0 / n);

        cout << "Applying alpha formula..." << endl;

        // here is where we apply our formula
        for (int i = 0; i < (int)adjm.size(); i++) {
            for (int j = 0; j < (int)adjm[i].size(); j++) {
                adjm[i][j] = alpha * adjm[i][j] + (1-alpha) * x[i];
            }
        }

        cout << "Performing iterations..." << endl;
        for (int i = 0; i < iterations; i++) {
            cout << "Iteration " << i + 1 << endl;
            adjm = multiplyMatrices(graph, adjm, adjm); // matrix formula from Markov Chains
        }

        vector<vector<double>> y;
        // transpose x for multiplication
        for (int i = 0; i < (int)x.size(); i++) {
            vector<double> temp(1, x[i]);
            y.push_back(temp);
        }
        // multiply the adjm with the starting vector
        y = multiplyMatrices(graph, adjm, y);

        // match indices and sort in descending order
        vector<int> idx(y.size());
        for (int i = 0; i < (int)idx.size(); i++) {
            idx[graph.getIndex(vertices[i])] = vertices[i].getID();
        }
        
        stable_sort(idx.begin(), idx.end(), [&y, &graph](int a, int b) { return y[graph.getIndex(a)][0] > y[graph.getIndex(b)][0]; });

        cout << "Creating vector..." << endl;
        for(auto i : idx) {
            page_list.push_back(make_pair(vertices[graph.getIndex(i)], y[graph.getIndex(i)][0]));
        }
        return page_list;
    }

    /**
     * Function to write the PageRank vector to a file.
     * @param pgrank: traversal vector from BFS function
     * @param filename: string containing path to output file
    */
    void BFSWriteToFile(vector<Vertex> traversal, string filename) {
        ofstream fs;
        fs.open(filename, std::ofstream::trunc);

        for (int i = 0; i < (int)traversal.size()-1; i++) {
            fs << traversal[i] << " -> ";
        }
        fs << traversal[traversal.size()-1];
        fs.close();
    }

    /**
     * Function to write the PageRank vector to a file.
     * @param pgrank: PageRank vector from PageRank function
     * @param filename: string containing path to output file
    */
    void PageRankWriteToFile(vector<pair<Vertex, double>> pgrank, string filename) {
        ofstream fs;
        fs.open(filename, std::ofstream::trunc);

        for (int i = 0; i < (int)pgrank.size(); i++) {
            fs << pgrank[i].first << "\t" << pgrank[i].second << endl;
        }
        fs.close();
    }
}