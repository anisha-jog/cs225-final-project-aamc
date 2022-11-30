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
 * ^         |
 * |         v
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
    g.insertEdge(6, 1);

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

// TEST_CASE("Copy constructor", "[ruleof3]") {
//     Graph g1 = SimpleGraph();
//     Graph g2(g1);

//     REQUIRE(g1 == g2);
// }

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

// TEST_CASE("simple graph incidence and adjacency", "[simpleGraph][incidentEdges][areAdjacent]") {
//     Graph g = SimpleGraph();

//     // incident edges size
//     REQUIRE(g.incidentEdges(1).size() == 1);
//     REQUIRE(g.incidentEdges(2).size() == 1);
//     REQUIRE(g.incidentEdges(3).size() == 0);

//     // incident edges contents
//     REQUIRE(g.incidentEdges(1)[0]->source == 1);
//     REQUIRE(g.incidentEdges(1)[0]->destination == 2);

//     REQUIRE(g.incidentEdges(2)[0]->source == 2);
//     REQUIRE(g.incidentEdges(2)[0]->destination == 3);

    
//     // areAdjacent
//     REQUIRE(g.areAdjacent(1, 2));
//     REQUIRE(g.areAdjacent(2, 3));
//     REQUIRE(!g.areAdjacent(1, 3));
// }



/*
* The graph for these tests are in web-small.txt
*/

TEST_CASE("vertices for connected graph is correct", "[constructor][vertices]") {
    // ifstream file("../web-small.txt");
    // Graph graph(file);
    // cout << "graph made" << endl;
    // auto v = graph.getVertices();
    // vector<int> actualLabels = {0, 1, 2, 3, 4, 5, 6};
    // cout << "vertices gotten" << endl;

    // REQUIRE(v.size() == actualLabels.size());
    
    // for (Vertex label : actualLabels) {
    //     REQUIRE(std::count(v.begin(), v.end(), label) == 1);
    // }
}
