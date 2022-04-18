#include "graph.h"
#include <cmath>

long long Graph::BoundaryPenalty(double p, double q){
    int Ip = static_cast<int>(p * 255), Iq = static_cast<int>(q * 255);
    return 100 * std::exp(-((Ip - Iq) * (Ip - Iq)) / (2 * SIGMA * SIGMA));
}

Graph::Graph(const PNG& png) : image(png) {
    SetNLinks();
    num_vertex = adj.size();
    source = adj.size() - 2;
    sink = adj.size() - 1;

}

Graph::Graph(const string& filename){
    image.readFromFile(filename);
    SetNLinks();
    num_vertex = adj.size();
    source = adj.size() - 2;
    sink = adj.size() - 1;
}

int Graph::id(int x, int y) const {
    return y * image.width() + x;
}

pair <int,int> Graph::coord(int id) const {
    return {id % image.width(), id / image.width()};
}
bool Graph::checkValid(int x, int y) const {
    return (x >= 0 && y >= 0 && x < (int)image.width() && y < (int)image.height());
}

void Graph::addEdge(int u, int v, int cap) {
    edges.push_back(Edge(u, v, cap));
    edges.push_back(Edge(v, u, 0));
    adj[u].push_back(num_edge);
    adj[v].push_back(num_edge + 1);
    num_edge += 2;
}

void Graph::SetNLinks(){
    vector <int> dx{-1, 1, 0, 0};
    vector <int> dy{0, 0, -1, 1};
    int n = image.width() * image.height();
    adj = vector<vector<int>>(n + 2);
    for(int x = 0; x < (int)image.width(); ++x){
        for(int y = 0; y < (int)image.height(); ++y){
            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (checkValid(nx, ny)) {
                    long long bp = BoundaryPenalty(image.getPixel(x, y).l, image.getPixel(nx, ny).l);
                    max_BP = std::max(max_BP, bp);
                    int u = id(x, y);
                    int v = id(nx, ny);
                    addEdge(u, v, bp);
                }
            }
        }
    }
}

void Graph::AddBSeed(unsigned x, unsigned y){
    int u = id(x, y);
    addEdge(source, u, max_BP);
}
void Graph::AddFSeed(unsigned x, unsigned y){
    int u = id(x, y);
    addEdge(u, sink, max_BP);
}

PNG Graph::draw(const vector<pair<int, int>>& background) const{
    PNG to_return = image;
    for(const pair<int,int>& p : background){
        HSLAPixel& pixel = to_return.getPixel(p.first,p.second);
        pixel.l -= 0.2;
        if(pixel.l < 0){
            pixel.l = 0;
        }
    }
    return to_return;
}