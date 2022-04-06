#pragma once

#include <vector>
#include <string>
#include "edge.h"

using std::vector;
using std::string;

class Graph {
  vector<Edge> edges; 
  vector<int> vertexes;

  Graph(string filename);
};