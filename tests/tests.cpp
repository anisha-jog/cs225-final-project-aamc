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
        cout << correct[i] << endl;
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



/*
* The graph for these tests are in web.tsv
*/

// TEST_CASE("vertices for connected graph is correct", "[constructor][vertices]") {
//     ifstream file("../web.tsv");
//     Graph graph(file);
//     cout << "graph made" << endl;
//     auto v = graph.getVertices();
//     vector<int> actualLabels = {0, 1, 2, 3, 4, 5, 6};
//     cout << "vertices gotten" << endl;

//     REQUIRE(v.size() == actualLabels.size());
    
//     for (Vertex label : actualLabels) {
//         REQUIRE(std::count(v.begin(), v.end(), label) == 1);
//     }
// }



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

// TEST_CASE("Disconnected BFS with input stream", "[BFS]") {
//     ifstream file("/workspaces/anushree/Desktop/cs225/cs225-final-project-aamc/web.txt");
//     Graph graph(file);

//     Vertex start = graph.getVertices().at(0);
//     std::vector<Vertex> result = algos::bfs(graph, start);

//     REQUIRE(result[0] == 1);
//     REQUIRE(result[1] == 2);
//     REQUIRE(result[2] == 3);
//     REQUIRE(result[3] == 4);
//     REQUIRE(result[4] == 5);
//     REQUIRE(result[5] == 6);
//     REQUIRE(result[6] == 7);
//     REQUIRE(result[7] == 0);
// }

TEST_CASE("Test  Disconnected Graph starting in the middle of vertex List" , "[BFS][defaultConstructor][disconnectedGraph]") {
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