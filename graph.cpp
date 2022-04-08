#include "graph.h"
#include <cmath>

long long Graph::BoundaryPenalty(double p, double q){
    int Ip = static_cast<int>(p * 255), Iq = static_cast<int>(q * 255);
    return 100 * std::exp(-((Ip - Iq) * (Ip - Iq)) / (2 * SIGMA * SIGMA));
}

Graph::Graph(PNG png) : image(png) {
    SetNLinks();
}

Graph::Graph(string filename){
    image.readFromFile(filename);
    SetNLinks();
}

void Graph::SetNLinks(){
    adj_vertexes = vector<vector<Edge*>>(image.width() * image.height() + 2);
    for(int x=0; x<(int)image.width(); ++x){
        for(int y=0; y<(int)image.height(); ++y){
            if(x-1 >= 0){ //left
                long long bp = BoundaryPenalty(image.getPixel(x,y).l, image.getPixel(x-1,y).l);
                if(bp > max_BP) max_BP = bp;
                edges.push_back(Edge(image.width()*y + x, image.width()*y + x-1, bp));
                adj_vertexes[image.width() * y + x].push_back(&edges.back());
            }
            if(x+1 < (int)image.width()){ //right
                long long bp = BoundaryPenalty(image.getPixel(x,y).l, image.getPixel(x+1,y).l);
                if(bp > max_BP) max_BP = bp;
                edges.push_back(Edge(image.width()*y + x, image.width()*y + x+1, bp));
                adj_vertexes[image.width() * y + x].push_back(&edges.back());
            }
            if(y-1 >= 0){ //up
                long long bp = BoundaryPenalty(image.getPixel(x,y).l, image.getPixel(x,y-1).l);
                if(bp > max_BP) max_BP = bp;
                edges.push_back(Edge(image.width()*y + x, image.width()*(y-1) + x, bp));
                adj_vertexes[image.width() * y + x].push_back(&edges.back());
            }
            if(y+1 < (int)image.height()){ //down
                long long bp = BoundaryPenalty(image.getPixel(x,y).l, image.getPixel(x,y+1).l);
                if(bp > max_BP) max_BP = bp;
                edges.push_back(Edge(image.width()*y + x, image.width()*(y+1) + x, bp));
                adj_vertexes[image.width() * y + x].push_back(&edges.back());
            }
        }
    }
}

void Graph::AddBSeed(unsigned x, unsigned y){
    edges.push_back(Edge(adj_vertexes.size()-2, image.width()*y + x, max_BP));
    adj_vertexes[adj_vertexes.size()-2].push_back(&edges.back());
    
}
void Graph::AddFSeed(unsigned x, unsigned y){
    edges.push_back(Edge(image.width()*y + x, adj_vertexes.size()-1, max_BP));
    adj_vertexes[image.width()*y + x].push_back(&edges.back());
}
