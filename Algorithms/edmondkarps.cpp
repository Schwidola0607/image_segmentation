#include "edmondkarps.h"
#include <iostream>

EdmondKarps::EdmondKarps(Graph* graph) : graph(graph) {}
long long EdmondKarps::bfs(int source, int target, vector <int>& parent) { // find augmenting path 
  fill(parent.begin(), parent.end(), -1);      
  queue <pair<int, long long>> queue;
  queue.push({source, INF});
  while (!queue.empty()) {
    int u = queue.front().first;
    long long flow = queue.front().second;
    queue.pop();
    for (int id: graph->adj[u]) {
      Edge e = graph->edges[id];
      int v = e.to;
      if (parent[v] == -1 && e.cap - e.flow > 0) { // if can be visited on the residual graph
        parent[v] = id; // mark parent for later updates on the residual graph
        int new_flow = std::min(flow, e.cap - e.flow);
        if (v == graph->sink) {
          return new_flow; // return augmenting path's flow
        }
        queue.push({v, new_flow});
      } 
    }
  }
  return 0LL; // 0 if not found any augmenting path
}
  
long long EdmondKarps::maxFlow() { // function to determine max flow
  long long flow = 0;
  vector <int> parent(graph->num_vertex);
  long long new_flow;
  while (true) {
    new_flow = bfs(graph->source, graph->sink, parent);
    // cout << new_flow << '\n';
    if (!new_flow) { // if no augmenting path found, halt
      break;
    }
    // cout << __LINE__ << '\n';
    flow += new_flow;
    int curr = graph->sink;
    while (curr != graph->source) {
      int id = parent[curr];
      int prev = graph->edges[id].from;
      graph->edges[id].flow += new_flow; // + flow for edge u->v
      graph->edges[id ^ 1].flow -= new_flow; // -flow for edge v-u 
      curr = prev;
    }
  }

  return flow;
}

vector <pair<int, int>> EdmondKarps::getBackground() {
  vector <pair<int, int>> background_pixels;
  vector <int> vis(graph->num_vertex - 2);
  queue <int> queue;
  queue.push(graph->source);
  vis[graph->source] = 1;
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    for (int id: graph->adj[u]) {
      int v = graph->edges[id].to;
      // if vertex v can be reached in the final residual graph, then v belongs to the cut containing source
      if (!vis[v] && graph->edges[id].cap - graph->edges[id].flow > 0) { 
        queue.push(v);
        vis[v] = 1;
      }
    }
  }

  for (int v = 0; v < (int)vis.size(); v++) {
    if (vis[v]) {
      background_pixels.push_back(graph->coord(v));
    }
  }

  return background_pixels;
}
