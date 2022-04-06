#pragma once

#include <vector>
#include <string>
#include "edge.h"
#include "cs225/PNG.h"

using std::vector;
using std::string;

class Graph {
  PNG image;
  vector<Edge> edges; 
  vector<vector<Edge*>> adj_vertexes;
  long long max_BP = 0;

  //takes in two luminance values from 0.0-1.0
  static long long BoundaryPenalty(double p, double q);
  static constexpr unsigned SIGMA = 30;

  public:
    //initializes graph with n-links
    Graph(string filename);

    //add t-link methods
    void AddBSeed(unsigned x, unsigned y);
    void AddFSeed(unsigned x, unsigned y);
};