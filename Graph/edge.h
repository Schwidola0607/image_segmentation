#pragma once

struct Edge {
  int from;
  int to;
  long long cap, flow = 0;

  Edge(int from, int to, long long cap): from(from), to(to), cap(cap){}
};
