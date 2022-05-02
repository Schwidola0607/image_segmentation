#pragma once

#include <vector>
#include <string>
#include "edge.h"
#include "../cs225/PNG.h"
#include <algorithm>

using std::vector;
using std::string;
using std::pair; 

using namespace cs225;

class Graph {
  public:
    PNG image;
    vector<Edge> edges; 
    vector<vector <int>> adj;
    long long max_BP = 0;
    int num_vertex;
    int num_edge;
    int source;
    int sink; 

    //takes in two luminance values from 0.0-1.0
    long long BoundaryPenalty(double p, double q) const;
    const unsigned SIGMA = 30;

    //helper used by both constructors to set n-links
    void SetNLinks();
    
    //helper used by SetBSeed and SetFseed()
    void addEdge(int u, int v, int cap);
    //helper used by SetNLinks
    void addEdgeNeighbor(int u, int v, int cap);
    int id(int x, int y) const;
    pair <int,int> coord(int id) const;
    bool checkValid(int x, int y) const;

    //initializes graph with n-links
    Graph(const PNG& png);
    Graph(const string& filename);
    //add t-link methods
    void AddBSeed(unsigned x, unsigned y);
    void AddFSeed(unsigned x, unsigned y);

    PNG draw(const vector<pair<int, int>>& background) const;
    PNG drawLine(const vector<pair<int,int>>& background) const;
};
