#include "graph.h"
#include <cmath>

static long long Graph::BoundaryPenalty(double p, double q){
    int Ip = static_cast<int>(p * 255), Iq = static_cast<int>(q * 255);
    return 100 * std::exp(-((Ip - Iq) * (Ip - Iq)) / (2 * SIGMA * SIGMA));
}

Graph::Graph(string filename){
    image.readFromFile(filename);

    //the second last vertex is the source and the last vertex is the sink
    adj_vertexes = vector<vector<Edge*>>(image.width() * image.height() + 2);

    for(int x=0; x<image.width(); ++x){
        for(int y=0; y<image.height(); ++y){
            if(x-1 >= 0){ //left
                long long bp = BoundaryPenalty(image.getPixel(x,y).l, image.getPixel(x-1,y).l);
                if(bp > max_BP) max_BP = bp;
                edges.push_back(Edge(image.width()*y + x, image.width()*y + x-1, bp));
                adj_vertexes[image.width() * y + x].push_back(&edges.back());
            }
            if(x+1 < image.width()){ //right
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
            if(y+1 < image.height()){ //down
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