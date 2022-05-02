#pragma once
#include <vector>
#include <algorithm>
#include "graph.h"
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::min; 

class Dinics {
  private:
    Graph* graph;
    const long long INF = INT64_MAX;
  public: 
    Dinics(Graph* graph);
    bool bfs(int source, int sink, vector <int>& dist);
    long long dfs(int source, int sink, long long flow, vector <int>& explore, vector <int> dist);
    long long maxFlow();
    vector <pair<int, int>> getBackground();
};