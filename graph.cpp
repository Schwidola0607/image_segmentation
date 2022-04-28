#include "graph.h"
#include <cmath>
#include <set>

using std::set;

long long Graph::BoundaryPenalty(double p, double q) const{
    double Ip = p * 255, Iq = (q * 255);
    return (long long)10000 * std::exp(-((Ip - Iq) * (Ip - Iq)) / (2.0 * this->SIGMA * this->SIGMA));
}

Graph::Graph(const PNG& png) : image(png) {
    num_edge = 0;
    SetNLinks();
    num_vertex = adj.size();
    source = adj.size() - 2;
    sink = adj.size() - 1;
}

Graph::Graph(const string& filename){
    image.readFromFile(filename);
    num_edge = 0;
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

void Graph::addEdgeNeighbor(int u, int v, int cap) {
    edges.push_back(Edge(u, v, cap));
    edges.push_back(Edge(v, u, cap));
    adj[u].push_back(num_edge);
    adj[v].push_back(num_edge + 1);
    num_edge += 2;
}

void Graph::SetNLinks(){
    vector <int> dx{1, 0};
    vector <int> dy{0, 1};
    int n = image.width() * image.height();
    adj = vector<vector<int>>(n + 2);
    for(int x = 0; x < (int)image.width(); ++x){
        for(int y = 0; y < (int)image.height(); ++y){
            for (int dir = 0; dir < 2; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (checkValid(nx, ny)) {
                    long long bp = BoundaryPenalty(image.getPixel(x, y).l, image.getPixel(nx, ny).l);
                    this->max_BP = std::max(max_BP, bp);
                    int u = id(x, y);
                    int v = id(nx, ny);
                    addEdgeNeighbor(u, v, bp);
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

    for(int x=0; x<static_cast<int>(to_return.width()); ++x){
        for(int y=0; y<static_cast<int>(to_return.height()); ++y){
            HSLAPixel& pixel = to_return.getPixel(x,y);
            pixel.s = 1;
            pixel.h = 120;
            pixel.l = 0.5;
        }
    }

    for(const auto& point : background){
        to_return.getPixel(point.first,point.second).h = 0;
    }

    return to_return;
}

PNG Graph::drawLine(const vector<pair<int, int>>& background) const{
    PNG to_return = image;

    set<pair<int,int>> background_set(background.begin(), background.end());
    for(int x=0; x<static_cast<int>(to_return.width()); ++x){
        for(int y=0; y<static_cast<int>(to_return.height()); ++y){
            if(background_set.count({x,y}) && 
            ((x > 0 && !background_set.count({x-1,y})) || 
            (x < static_cast<int>(to_return.width()) - 1 && !background_set.count({x+1,y})) || 
            (y > 0 && !background_set.count({x,y-1})) || 
            (y < static_cast<int>(to_return.height()) - 1 && !background_set.count({x,y+1})))){
                to_return.getPixel(x,y) = HSLAPixel(0,1,0.5);
            }
        }
    }
    return to_return;
}