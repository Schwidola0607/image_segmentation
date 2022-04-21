#include "edmondkarps.h"
EdmondKarps::EdmondKarps(Graph* g) : g(g) {}
long long EdmondKarps::bfs(int s, int t, vector <int>& parent) {
  fill(parent.begin(), parent.end(), -1);      
  queue <pair<int, long long>> q;
  q.push({s, INF});
  while (!q.empty()) {
    int u = q.front().first;
    long long flow = q.front().second;
    q.pop();

    for (int id: g->adj[u]) {
      Edge e = g->edges[id];
      int v = e.to;
      if (parent[v] == -1 && e.cap - e.flow > 0) {
        parent[v] = id;
        int new_flow = std::min(flow, e.cap - e.flow);
        if (v == g->sink) {
          return new_flow;
        }
        q.push({v, new_flow});
      } 
    }
  }
  return 0LL;
}
  
long long EdmondKarps::maxFlow() {
  long long flow = 0;
  vector <int> parent(g->num_vertex);
  long long new_flow;
  while (true) {
    new_flow = bfs(g->source, g->sink, parent);
    if (!new_flow) {
      break;
    }
    flow += new_flow;
    int curr = g->sink;
    while (curr != g->source) {
      int id = parent[curr];
      int prev = g->edges[id].from;
      g->edges[id].flow += new_flow;
      g->edges[id ^ 1].flow -= new_flow;
      curr = prev;
    }
  }

  return flow;
}

vector <pair<int, int>> EdmondKarps::getBackground() {
  vector <pair<int, int>> background_pixels;
  vector <int> vis(g->num_vertex - 2);
  queue <int> q;
  q.push(g->source);
  vis[g->source] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int id: g->adj[u]) {
      int v = g->edges[id].to;
      if (!vis[v] && g->edges[id].cap - g->edges[id].flow > 0) {
        q.push(v);
        vis[v] = 1;
      }
    }
  }

  for (int v = 0; v < (int)vis.size(); v++) {
    if (vis[v]) {
      background_pixels.push_back(g->coord(v));
    }
  }

  return background_pixels;
}
