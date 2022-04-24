#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int from;
  int to;
  long long cap, flow = 0;

  Edge(int from, int to, long long cap): from(from), to(to), cap(cap){}

  //comparison operators - compares weights only
  bool operator>(const Edge& other_edge) const {return cap > other_edge.cap;}
  bool operator==(const Edge& other_edge) const {return cap == other_edge.cap;}
  bool operator!=(const Edge& other_edge) const {return !(*this == other_edge);}
  bool operator<(const Edge& other_edge) const {return cap < other_edge.cap;}
  bool operator>=(const Edge& other_edge) const {return *this > other_edge || *this == other_edge;}
  bool operator<=(const Edge& other_edge) const {return *this < other_edge || *this == other_edge;}
};

class Graph {
  public:
    vector<Edge> edges; 
    vector<vector <int>> adj;
    long long max_BP = 0;
    int num_vertex;
    int num_edge;
    int source;
    int sink; 

    //takes in two luminance values from 0.0-1.0
    static long long BoundaryPenalty(double p, double q);
    static constexpr unsigned SIGMA = 30;

    //helper used by both constructors to set n-links
    void SetNLinks();
    
    //helper used by SetNLinks()
    void addEdge(int u, int v, int cap);
    int id(int x, int y) const;
    pair <int,int> coord(int id) const;
    bool checkValid(int x, int y) const;

    //add t-link methods
    void AddBSeed(unsigned x, unsigned y);
    void AddFSeed(unsigned x, unsigned y);
};
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

const long long INF = INT64_MAX;
Dinics::Dinics(Graph* g) : g(g) {}
bool Dinics::bfs(int s, int t, vector <int>& dist) {
  queue <int> q({s});
  fill(dist.begin(), dist.end(), -1); 
  dist[s] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    // if (u == t) cout << "hi";
    if (u == t) break;
    for (int i : g -> adj[u]) {
      Edge e = g->edges[i];
      if (dist[e.to] == -1 && e.cap > e.flow) {
        q.push(e.to);
        dist[e.to] = dist[u] + 1;
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
      long long temp = dfs(e.to, t, curr, explore, dist);
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

void Graph::addEdge(int u, int v, int cap) {
    edges.push_back(Edge(u, v, cap));
    edges.push_back(Edge(v, u, 0));
    adj[u].push_back(num_edge);
    adj[v].push_back(num_edge + 1);
    num_edge += 2;
}

int main() {
  int n, m;
  cin >> n >> m;
  Graph g;
  g.adj = vector<vector<int>>(n + 3);
  g.num_vertex = n + 3;
  g.source = 1;
  g.sink = n;
  g.num_edge = 0;
  for (int i = 0; i < m; i++) {
    int u, v;
    long long cap;
    cin >> u >> v >> cap;
    g.addEdge(u, v, cap);
  }
  // EdmondKarps ekarps(&g);
  // cout << ekarps.maxFlow() << '\n';
  Dinics dinics(&g);
  cout << dinics.maxFlow() << '\n';
} 