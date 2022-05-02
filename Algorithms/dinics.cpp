#include "dinics.h"
Dinics::Dinics(Graph* graph) : graph(graph) {} //Instantiating a graph
bool Dinics::bfs(int source, int sink, vector <int>& dist) { //Checking if there is a path from source to sink
  queue <int> nodes({source});
  fill(dist.begin(), dist.end(), -1); //Creating a level graph which is used in dfs
  dist[source] = 0;
  while (!nodes.empty()) { 
    int curr = nodes.front(); 
    nodes.pop();
    if (curr == sink) break;
    for (int index : graph -> adj[curr]) {
      Edge edge = graph->edges[index];
      if (dist[edge.to] == -1 && edge.cap > edge.flow) { //If there is a flow towards said node, add it to bfs
        nodes.push(edge.to);
        dist[edge.to] = dist[curr] + 1;
      }
    }
  }
  return dist[sink] != -1; 
}
long long Dinics::dfs(int source, int sink, long long flow, vector <int>& explore, vector <int> dist) { //Updating each path's flow from source to sink
  if (source == sink || flow == 0) return flow;
  for (; explore[source] < (int)graph -> adj[source].size(); ++explore[source]) { //Iterating through edges
    Edge& edge = graph -> edges[graph -> adj[source][explore[source]]];
    Edge& other_edge = graph -> edges[graph -> adj[source][explore[source]]^1];
    if (dist[edge.to] == dist[edge.from] + 1 && edge.flow < edge.cap) { //Condition to check -> updating the path's flow
      long long curr = min(flow, edge.cap - edge.flow);
      long long temp = dfs(edge.to, sink, curr, explore, dist);
      if (temp > 0) {
        edge.flow += temp;
        other_edge.flow -= temp;
        return temp;
      }
    }
  }
  return 0;
}
long long Dinics::maxFlow() { //Gets the max flow of the graph while also running the algorithm
  long long flow = 0;
  vector <int> dist(graph -> num_vertex); //Class variables to help with computing
  vector <int> explore(graph -> num_vertex); 
  while (bfs(graph -> source, graph -> sink, dist)) {
    while (true) { 
      fill(explore.begin(), explore.end(), 0);
      long long new_flow = dfs(graph -> source, graph -> sink, INF, explore, dist); //Calculating the flow
      if (new_flow == 0) break;
      flow += new_flow;
    }
  }
  return flow;
}
vector <pair<int, int>> Dinics::getBackground() { //Separates the background from the foreground
  vector <pair<int, int>> background_pixels;
  vector <int> vis(graph->num_vertex-2); 
  queue <int> nodes;
  nodes.push(graph->source);
  vis[graph->source] = 1;
  while (!nodes.empty()) { //Runs bfs to iterate through all nodes
    int curr = nodes.front();
    nodes.pop();
    for (int index: graph->adj[curr]) {
      int curr = graph->edges[index].to;
      if (!vis[curr] && graph->edges[index].cap - graph->edges[index].flow > 0) { //Checks if said pixel is a background or foreground pixel
        nodes.push(curr);
        vis[curr] = 1;
      }
    }
  }
  for (int index = 0; index < (int)vis.size(); index++) { //Adds all the background nodes into a vector
    if (vis[index]) {
      background_pixels.push_back(graph->coord(index));
    }
  }
  return background_pixels;
}