#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

#include "graph.h"
#include "algorithms.hpp"

using std::ifstream; 
using std::string;
using std::vector;
using Edge = Graph::Edge;
using Vertex = Graph::Vertex;
using namespace std;
using namespace algos;


/* Helper functions for building graphs to use for different test cases */

/*
* a simple graph:
* A --> B --> C
*/
Graph SimpleGraph() {
    Graph g;

    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);

    g.insertEdge(1, 2);
    g.insertEdge(2, 3);

    return g;
}

/*
 * A disconnected graph:
 *
 * 1 -> 2
 *  |/
 *  v      5 -> 6 -> 7
 *  3 -> 4
 */
Graph DisconnectedGraph() {
    Graph g;

    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    g.insertVertex(7);

    g.insertEdge(1, 2);
    g.insertEdge(1, 3);
    g.insertEdge(2, 3);
    g.insertEdge(3, 4);
    g.insertEdge(5, 6);
    g.insertEdge(6, 7);

    return g;
}

/*
 * A circular graph:
 *
 * 1 -> 2 -> 3
 *           |
 *           v
 * 6 <- 5 <- 4
 * 
 */ 
Graph CircleGraph() {
    Graph g;
    
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);

    g.insertEdge(1, 2);
    g.insertEdge(2, 3);
    g.insertEdge(3, 4);
    g.insertEdge(4, 5);
    g.insertEdge(5, 6);

    return g;
}


/* Rule Of 3 Tests */
TEST_CASE("Equals operator", "[ruleof3]") {
    Graph g1 = DisconnectedGraph();
    Graph g2 = DisconnectedGraph();
    Graph g3 = CircleGraph();

    REQUIRE(g1 == g2);
    REQUIRE(!(g2 == g3));
}

TEST_CASE("Copy constructor", "[ruleof3]") {
    Graph g1 = SimpleGraph();
    Graph g2(g1);

    REQUIRE(g1 == g2);
}

TEST_CASE("Assignment operator", "[ruleof3]") {
    Graph g1 = SimpleGraph();
    Graph g2 = g1;
    REQUIRE(g2 == SimpleGraph());
}


/* GRAPH IMPLEMENTATION TESTS */
TEST_CASE("insert vertices in a simple graph ", "[simpleGraph][vertices][insertVertex]") {
    Graph g = SimpleGraph();
    vector<Vertex> vertices = g.getVertices();

    // create the correct vertices
    vector<Vertex> correct;
    for (int i = 1; i <= (int)vertices.size(); i++) {
        correct.push_back(Vertex(i));
    }

    REQUIRE(vertices.size() == 3);

    for (int i = 0; i < (int)vertices.size() && i < (int)correct.size(); i++) {
        REQUIRE(std::count(vertices.begin(), vertices.end(), correct[i]) == 1);
    }
}

TEST_CASE("simple graph incidence and adjacency", "[simpleGraph][incidentEdges][areAdjacent]") {
    Graph g = SimpleGraph();

    // incident edges size
    REQUIRE(g.incidentEdges(1).size() == 1);
    REQUIRE(g.incidentEdges(2).size() == 1);
    REQUIRE(g.incidentEdges(3).size() == 0);

    // incident edges contents
    REQUIRE(g.incidentEdges(1)[0]->source == 1);
    REQUIRE(g.incidentEdges(1)[0]->destination == 2);

    REQUIRE(g.incidentEdges(2)[0]->source == 2);
    REQUIRE(g.incidentEdges(2)[0]->destination == 3);
}

TEST_CASE("vertices for connected graph are correct", "[constructor][vertices]") {
    string file("../input/web-connected.tsv");
    Graph graph(file);
    auto v = graph.getVertices();
    vector<int> actualLabels = {0, 1, 2, 3, 4, 5, 6};

    REQUIRE(v.size() == actualLabels.size());
    
    for (Vertex label : actualLabels) {
        REQUIRE(std::count(v.begin(), v.end(), label) == 1);
    }
}


/* BFS ALGORITHM TEST CASES */
TEST_CASE("Test Circular BFS Traversal", "[BFS]") {
    Graph graph = CircleGraph();
    Vertex start = graph.getVertices().at(0);
    std::vector<Vertex> result = algos::bfs(graph, start);

    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 2);
    REQUIRE(result[2] == 3);
    REQUIRE(result[3] == 4);
    REQUIRE(result[4] == 5);
    REQUIRE(result[5] == 6);
}

TEST_CASE("Test Disconnected BFS Traversal", "[BFS]") {
    Graph graph = DisconnectedGraph();

    Vertex start = graph.getVertices().at(0);
    std::vector<Vertex> result = algos::bfs(graph, start);

    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 3);
    REQUIRE(result[2] == 2);
    REQUIRE(result[3] == 4);
    REQUIRE(result[4] == 5);
    REQUIRE(result[5] == 6);
    REQUIRE(result[6] == 7);
}

TEST_CASE("BFS with One vertex", "[BFS]") {
    Graph graph;
    graph.insertVertex(1);

    Vertex start = graph.getVertices().at(0);
    std::vector<Vertex> result = algos::bfs(graph, start);

    REQUIRE(result[0] == 1);
}

TEST_CASE("Disconnected BFS with input stream", "[BFS]") {
    string file("../input/web-connected.tsv");
    Graph graph(file);

    Vertex start = graph.getVertices().at(0);
    std::vector<Vertex> result = algos::bfs(graph, start);

    REQUIRE(result[0] == 0);
    REQUIRE(result[1] == 1);
    REQUIRE(result[2] == 2);
    REQUIRE(result[3] == 3);
    REQUIRE(result[4] == 4);
    REQUIRE(result[5] == 5);
    REQUIRE(result[6] == 6);
}

TEST_CASE("Test Disconnected Graph starting in the middle of vertex List" , "[BFS][defaultConstructor][disconnectedGraph]") {
    Graph graph = DisconnectedGraph();

    Vertex start = graph.getVertices().at(4);
    std::vector<Vertex> result = algos::bfs(graph, start);

    REQUIRE(result[0] == 5);
    REQUIRE(result[1] == 6);
    REQUIRE(result[2] == 7);
    REQUIRE(result[3] == 1);
    REQUIRE(result[4] == 3);
    REQUIRE(result[5] == 2);
    REQUIRE(result[6] == 4);
}


/* PAGERANK ALGORITHM TEST CASES */
TEST_CASE("PageRank on graph with no edges is all the same", "[PageRank][disconnectedGraph]") {
    Graph g;

    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    g.insertVertex(7);

    vector<pair<Vertex, double>> v = pageRank(g);

    for (int i = 0; i < (int)v.size(); i++) {
        REQUIRE(v[i].second == 1.0 / v.size());
    }
}

TEST_CASE("PageRank on small graph", "[PageRank]") {
    Graph g("../input/web-small.txt");

    vector<pair<Vertex, double>> v = pageRank(g);

    REQUIRE(v[0].first.getID() == 4);
    REQUIRE(v[1].first.getID() == 1);
    REQUIRE(v[2].first.getID() == 3);
    REQUIRE(v[3].first.getID() == 2);
    REQUIRE(v[4].first.getID() == 0);
}

TEST_CASE("simple graph adjacency matrix", "[defaultConstructor][simpleGraph][adjacencyMatrix]") {
    Graph graph = SimpleGraph();

    graph.createAdjM();

    vector<vector<double>> mat = graph.getAdjM();
    
    REQUIRE(mat.size() == 3);
    REQUIRE(mat[0].size() == 3);

    REQUIRE(mat[1][0] == 1);
    REQUIRE(mat[2][1] == 1);
    REQUIRE(mat[0][0] == 0);
    REQUIRE(mat[1][1] == 0);
    REQUIRE(mat[2][2] == 1.0 / 3.0);
    REQUIRE(mat[0][1] == 0);
    REQUIRE(mat[1][2] == 1.0 / 3.0);
    REQUIRE(mat[0][2] == 1.0 / 3.0);
    REQUIRE(mat[2][0] == 0);
}

TEST_CASE("PageRank on connected graph is correct", "[connectedGraph]") {
    Graph graph("../input/web-connected.tsv");

    vector<pair<Vertex, double>> v = pageRank(graph, 0.85, 1);

    // all of the other vertices should have the same pagerank value, just 0 should be at the bottom
    // this is because 0 has no incoming edges
    for (int i = 0; i < (int)v.size() - 2; i++) {
        REQUIRE(std::ceil(v[i].second * 100.0) / 100.0 == std::ceil(v[i+1].second * 100.0) / 100.0);
    }
    REQUIRE(v[v.size() - 1].first == 0);
}

TEST_CASE("Adjacency matrix for disconnected graph is correct", "[disconnectedGraph][adjacencyMatrix]") {
    Graph graph("../input/web-disconnected.tsv");

    // the graph will read vertices in the order 1 2 3 0 4 6 5
    vector<vector<double>> true_adj = {{0, 0, 1.0 / 7.0, 0, 0, 0, 0},
                                        {1, 0, 1.0 / 7.0, 1, 0, 0, 0},
                                        {0, 1, 1.0 / 7.0, 0, 0, 0, 0},
                                        {0, 0, 1.0 / 7.0, 0, 0, 0, 0},
                                        {0, 0, 1.0 / 7.0, 0, 0, 0, 1},
                                        {0, 0, 1.0 / 7.0, 0, 1, 0, 0},
                                        {0, 0, 1.0 / 7.0, 0, 0, 1, 0}};

    graph.createAdjM();
    vector<vector<double>> adjm = graph.getAdjM();

    REQUIRE(adjm.size() == true_adj.size());
    REQUIRE(adjm[0].size() == true_adj[0].size());

    for (int i = 0; i < (int)adjm.size(); i++) {
        for (int j = 0; j < (int)adjm[i].size(); j++) {
            REQUIRE(adjm[i][j] == true_adj[i][j]);
        }
    }
}

TEST_CASE("Disconnected graph PageRank", "[disconnectedGraph][PageRank]") {
    Graph graph("../input/web-disconnected.tsv");

    vector<double> expected_scores = {0.238138, 0.238138, 0.238138, 0.1177, 0.0964458,
                                      0.0357207, 0.0357207};

    auto results = pageRank(graph);
    vector<double> actual_scores;
    std::transform(results.begin(), results.end(), std::back_inserter(actual_scores), [](auto pair) { return pair.second; });

    for (int i = 0; i < (int)actual_scores.size(); i++) {
        REQUIRE(std::ceil(expected_scores[i] * 100.0) / 100.0 == std::ceil(actual_scores[i] * 100.0) / 100.0);
    }
}

TEST_CASE("Complex graph PageRank", "[complexGraph][pageRank]") {
    Graph graph("../input/web-complex.txt");

    vector<double> expected_scores = {0.21098858, 0.15846934, 0.15011459, 0.10217013, 0.09473939,
        0.06646371, 0.06348671, 0.05946397, 0.05660358, 0.0125, 0.0125, 0.0125};

    auto results = pageRank(graph);
    vector<double> actual_scores;
    std::transform(results.begin(), results.end(), std::back_inserter(actual_scores), [](auto pair) { return pair.second; });

    for (int i = 0; i < (int)actual_scores.size(); i++) {
        REQUIRE(std::ceil(expected_scores[i] * 100.0) / 100.0 == std::ceil(actual_scores[i] * 100.0) / 100.0);
    }
}