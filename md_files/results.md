# Algorithm Results
Detailed results of our chosen algorithms

## Dinics

### Algorithm Summary
Dinic's Algorithm works as follows: <br/>
1. Runs BFS to test if a a path from source to sink exists.
2. Within that BFS, construct a level graph and store it to the distance vector.
3. Within the level graph, continuously run DFS from source to sink until no more flow can be sent (also known as a blocking flow).
4. In addition to this in DFS, calculating the max flow is done by summing the bottleneck values of each augmenting path. 
5. Repeat 1-4 until a BFS finds no path from source to sink (and then one can subsequently call getBackground with no issues). <br/> <br/>
This is the code within the maxFlow method and references all the important steps to run Dinic's Algorithm: 
```cpp
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
```
### Other Information
* O(V^2 x E), where V is the number of vertices and E is the number of edges. Also, this is the guaranteed known run time of Dinics.
* Testing is detailed below, and it passes both Max Flow and getBackground tests.

## Edmond-Karps

Edmond-Karps's Algorithm works as follows: <br/>
1. Runs BFS to test if there's an augmenting path from source to sink.
2. Within that BFS, construct a bfs-tree to later trace back the augmenting path.
4. In the maxflow function, check if the return value of BFS is 0 or not (still have a augmenting path or not).
5. If no break, If yes push flow and push -flow in reverse edges accordingly.
6. Repeat 1-5 until a BFS finds no path from source to sink.
7. Call getBackground() on the final residual graph to get the cut we want.
<br/> <br/>
This is the code within the maxFlow method and references all the important steps to run Edmond-Karp's Algorithm: 
```cpp
long long EdmondKarps::maxFlow() { // function to determine max flow
  long long flow = 0;
  vector <int> parent(graph->num_vertex);
  long long new_flow;
  while (true) {
    new_flow = bfs(graph->source, graph->sink, parent);
    if (!new_flow) { // if no augmenting path found, halt
      break;
    }
    flow += new_flow;
    int curr = graph->sink;
    while (curr != graph->source) {
      int id = parent[curr];
      int prev = graph->edges[id].from;
      graph->edges[id].flow += new_flow; // + flow for edge u->v
      graph->edges[id ^ 1].flow -= new_flow; // -flow for edge v-u 
      curr = prev;
    }
  }
  return flow;
}
```
### Other Information
* O(V x E^2), where V is the number of vertices and E is the number of edges. Also, this is the guaranteed known run time of Edmond-Karps.
* Testing is detailed below, and it passes both Max Flow and getBackground tests.

## Testing
We used Max FLow tests from [this](https://cses.fi/problemset/task/1694/) competitive programming problem.
We also make 3x3 high constrasity tests to test our getBackground, draw, drawLines, and other functionalities. 

Because of this detailed testing scheme, we have realized multiple bugs in our development process (bugs in Dincis, bugs in how build our graph).

## Conclusion 

* Ultimately, we found that our algorithms successfully divided a given image into its foreground and background, and these images would be usable in fields that require this information (i.e. automated driving, computer vision, etc) based on our given max flow and getBackground tests. 
* Besides the notable runtime differences, 
* Still, we would implement these changes with more time: 
  * Implementing more flow algorithms, particularly Push-Relabel, would allow us to review the different intricacies between each algorithm. 
  * Creating our own dataset would allow for more clearer image cuts, as we could utilize better seeds and highlight the overall difference between foreground and background. 
  * Implement some algorithms to penalize bad cuts, prioritise cut with more vertex, (even cut for fore/background)
