#pragma once
#include <vector>
#include <algorithm>
#include "graph.h"
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::min; 

const long long INF = INT64_MAX;

class EdmondKarps {
  private:
    Graph* g;
  public: 
    EdmondKarps(Graph* g);
    long long bfs(int s, int t, vector <int>& parent);
    long long maxFlow();
    vector <pair<int, int>> getBackground();
};