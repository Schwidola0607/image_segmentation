#pragma once

struct Edge {
  int from;
  int to;
  long long weight;

  Edge(int from, int to, long long weight): from(from), to(to), weight(weight){}

  //comparison operators - compares weights only
  bool operator>(const Edge& other_edge) const {return weight > other_edge.weight;}
  bool operator==(const Edge& other_edge) const {return weight == other_edge.weight;}
  bool operator!=(const Edge& other_edge) const {return !(*this == other_edge);}
  bool operator<(const Edge& other_edge) const {return weight < other_edge.weight;}
  bool operator>=(const Edge& other_edge) const {return *this > other_edge || *this == other_edge;}
  bool operator<=(const Edge& other_edge) const {return *this < other_edge || *this == other_edge;}
};
