#pragma once

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
