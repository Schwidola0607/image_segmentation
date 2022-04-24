#include "../cs225/catch/catch.hpp"

#include "../cs225/PNG.h"
#include "../dinics.h"
#include "../graph.h"
#include "../edmondkarps.h"

#include <vector>
#include <utility>

using std::vector;
using std::pair;

PNG drawDinics(Graph& g){
    Dinics dinics(&g);
    long long max_flow = dinics.maxFlow();
    vector <pair <int, int>> bg_pixels = dinics.getBackground();
    
    return g.draw(bg_pixels);
}

TEST_CASE("Dinics 3x3 #1"){
    Graph g("tests/3x3tests/1.png");
    g.AddFSeed(2,1);
    g.AddBSeed(1,1);
    g.AddBSeed(0,0);
    
    PNG expected;
    expected.readFromFile("tests/3x3tests/1_expected.png");
    PNG actual = drawDinics(g);
    actual.writeToFile("tests/3x3tests/1_actual.png");
    REQUIRE(expected == actual);
}

TEST_CASE("Dinics 3x3 #2"){
    Graph g("tests/3x3tests/2.png");
    g.AddFSeed(1,0);
    g.AddFSeed(1,1);
    g.AddBSeed(1,2);
    
    PNG expected;
    expected.readFromFile("tests/3x3tests/2_expected.png");
    PNG actual = drawDinics(g);
    actual.writeToFile("tests/3x3tests/2_actual.png");
    REQUIRE(expected == actual);
}

TEST_CASE("Dinics 3x3 #3"){
    Graph g("tests/3x3tests/3.png");
    g.AddFSeed(1,1);
    g.AddFSeed(1,2);
    g.AddBSeed(2,0);
    g.AddBSeed(2,1);
    
    PNG expected;
    expected.readFromFile("tests/3x3tests/3_expected.png");
    PNG actual = drawDinics(g);
    actual.writeToFile("tests/3x3tests/3_actual.png");
    REQUIRE(expected == actual);
}

TEST_CASE("Dinics 3x3 #4"){
    Graph g("tests/3x3tests/4.png");
    g.AddFSeed(0,1);
    g.AddFSeed(2,1);
    g.AddFSeed(1,0);
    g.AddBSeed(1,2);
    
    PNG expected;
    expected.readFromFile("tests/3x3tests/4_expected.png");
    PNG actual = drawDinics(g);
    actual.writeToFile("tests/3x3tests/4_actual.png");
    REQUIRE(expected == actual);
}

TEST_CASE("Dinics 3x3 #5"){
    Graph g("tests/3x3tests/5.png");
    g.AddFSeed(1,2);
    g.AddBSeed(2,0);
    g.AddBSeed(2,2);
    g.AddBSeed(0,0);
    g.AddBSeed(1,1);
    
    PNG expected;
    expected.readFromFile("tests/3x3tests/5_expected.png");
    PNG actual = drawDinics(g);
    actual.writeToFile("tests/3x3tests/5_actual.png");
    REQUIRE(expected == actual);
}