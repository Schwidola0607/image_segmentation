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
long long Dinics::maxFlow() {
  long long flow = 0;
  vector <int> dist(g->num_vertex);
  vector <int> explore(g->num_vertex);
  while (bfs(g -> source, g -> sink, dist)) {
    while (true) {
      fill(explore.begin(), explore.end(), 0);
      long long new_flow = dfs(g -> source, g -> sink, INF, explore, dist);
      if (new_flow == 0) break;
      flow += new_flow;
    }
  }
  return flow;
}
```
### Other Information
* O(V^2 x E), where V is the number of vertex and E is the number of edges. Also, this is the guaranteed known run time of Dinics.
* Testing is detailed below, and it passes both max flow and getBackground tests.

## Edmond-Karps

Big o, summarize the process, add some visuals if needed

## Testing

Add in our image seg/max flow testing and showcase how it's done

## Conclusion 

* Ultimately, we found that our algorithms successfully divided a given image into its foreground and background, and these images would be usable in fields that require this information (i.e. automated driving, computer vision, etc) based on our given max flow and getBackground tests. 
* Besides the notable runtime differences, 
* Still, we would implement these changes with more time: <br/>
      * Implementing more flow algorithms, particularly Push-Relabel, would allow us to review the different intricacies between each algorithm. <br/>
      * Creating our own dataset would allow for more clearer image cuts, as we could utilize better seeds and highlight the overall difference between foreground and background. <br/>
