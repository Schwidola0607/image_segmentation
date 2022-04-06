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
  vector<int> vertexes;

  //takes in two luminance values from 0.0-1.0
  static long long BoundaryPenalty(double p, double q);
  static constexpr unsigned SIGMA = 30;

  public:
    //initializes graph with n-links
    Graph(string filename);

    //add t-link methods
    AddBSeed(unsigned x, unsigned y);
    AddFSeed(unsigned x, unsigned y);
};