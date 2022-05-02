#pragma once
#include <vector>
#include <algorithm>
#include "../Graph/graph.h"
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::min; 

// const long long INF = INT64_MAX;

class Dinics {
  private:
    Graph* g;
    const long long INF = INT64_MAX;
  public: 
    Dinics(Graph* g);
    bool bfs(int s, int t, vector <int>& dist);
    long long dfs(int s, int t, long long flow, vector <int>& explore, vector <int> dist);
    long long maxFlow();
    vector <pair<int, int>> getBackground();
};