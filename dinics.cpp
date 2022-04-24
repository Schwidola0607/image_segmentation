#include "dinics.h"
Dinics::Dinics(Graph* g) : g(g) {}
bool Dinics::bfs(int s, int t, vector <int>& dist) {
  queue <int> q({s});
  fill(dist.begin(), dist.end(), -1); 
  dist[s] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (u == t) break;
    for (int i : g -> adj[u]) {
      Edge e = g->edges[i];
      if (dist[i] == -1 && e.cap > e.flow) {
        q.push(i);
        dist[i] = dist[u] + 1;
      }
    }
  }
  return dist[t] != -1;
}
long long Dinics::dfs(int s, int t, long long flow, vector <int>& explore, vector <int> dist) {
  if (s == t || flow == 0) return flow;
  for (; explore[s] < (int)g -> adj[s].size(); ++explore[s]) {
    Edge& e = g -> edges[g -> adj[s][explore[s]]];
    Edge& oe = g -> edges[g -> adj[s][explore[s]]^1];
    if (dist[e.to] == dist[e.from] + 1 && e.flow < e.cap) {
      long long curr = min(flow, e.cap - e.flow);
      long long temp = dfs(g -> adj[s][explore[s]], t, curr, explore, dist);
      if (temp > 0) {
        e.flow += temp;
        oe.flow -= temp;
        return temp;
      }
    }
  }
  return 0;
}
long long Dinics::maxFlow() {
  long long flow = 0;
  vector <int> dist(g->num_vertex);
  vector <int> explore(g->num_vertex);
  while (true) {
    if (!bfs(g -> source, g -> sink, dist)) break;
    while (true) {
      fill(explore.begin(), explore.end(), 0);
      long long new_flow = dfs(g -> source, g -> sink, INF, explore, dist);
      if (new_flow == 0) break;
      flow += new_flow;
    }
  }
  return flow;
}
vector <pair<int, int>> Dinics::getBackground() {
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