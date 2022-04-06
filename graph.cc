#include "graph.h"
#include <cmath>

static long long Graph::BoundaryPenalty(double p, double q){
    int Ip = static_cast<int>(p * 255), Iq = static_cast<int>(q * 255);
    return 100 * std::exp(-((Ip - Iq) * (Ip - Iq)) / (2 * SIGMA * SIGMA));
}

Graph::Graph(string filename){
    image.readFromFile(filename);

    for(int x=0; x<input.width(); ++x){
        for(int y=0; y<input.height(); ++y){
            vertexes.push_back(input.width()*y + x);
            if(x-1 >= 0){ //left
                edges.push_back(Edge((input.width()*y + x, input.width()*y + x-1, BoundaryPenalty(image.getPixel(x,y).l, image.getPixel(x-1,y).l))));
            }
            if(x+1 < input.width()){ //right
                edges.push_back(Edge((input.width()*y + x, input.width()*y + x+1, BoundaryPenalty(image.getPixel(x,y).l, image.getPixel(x+1,y).l))));
            }
            if(y-1 >= 0){ //up
                edges.push_back(Edge((input.width()*y + x, input.width()*(y-1) + x, BoundaryPenalty(image.getPixel(x,y).l, image.getPixel(x,y-1).l))));
            }
            if(y+1 < input.height()){ //down
                edges.push_back(Edge((input.width()*y + x, input.width()*(y+1) + x, BoundaryPenalty(image.getPixel(x,y).l, image.getPixel(x,y+1).l))));
            }
        }
    }
    //first one is the source, second one is the sink
    vertexes.push_back(input.width() * input.height());
    vertexes.push_back(input.width() * input.height() + 1);
}