# Final Project Proposal

## Leading Question
* Use network flow algorithms to divide small greyscale images into their foreground and background.

## Dataset Acquisition and Processing
* **Data Format\:** We will use the CIFAR-10 dataset (https://www.cs.toronto.edu/~kriz/cifar.html). The dataset consists of 60000 32x32 color images stored in 6 separate binary files. We will use a subset of this dataset consisting of 1000 randomly chosen images.
* **Data Correction\:** Since the input dataset does not come as PNGs, we will have to do some preprocessing work in a Python notebook to produce our 1000 PNG sample. To simplify things, we also want our PNGs to be grayscale so we will pass those images into lab_intro’s grayscale function.
* **Data Storage\:**
  * A pixel in the image is a vertex in the graph labeled in row-major order. These vertices are called pixel vertices. In addition, there are two extra vertices that serve as the source and the sink.
  * There are two types of edges in this graph: n-links, which connect neighboring pixels and t-links connect the pixels with the source vertex and sink vertex.
  * We will store a list of PNG objects and then we will transform it to a list of graphs as described above. 
  * Total storage cost:
    * O(Number of images x Number of pixels in an image) where the number of images is ~ 1000 and the number of pixels is 32 x 32.

## Graph Algorithms
### Dinic's algorithm 
(BFS is used implicitly in Dinic’s algorithm implementation)
* **Function inputs:**
  * A Graph (described above)
* **Function outputs:**
  * A 32 x 32 PNG with a red line to signify the image segmentation
* **Function efficiency:**
  * O(V^2 x E), where V is the number of vertex and E is the number of edges. Based on how we build the graph, E ~ 4 * V, so O(V^3)
### Edmond-Karps algorithm
Same inputs and outputs as Dinic’s but runs in O(V x E^2), where V is the number of vertex and E is the number of edges. Based on how we build the graph, E ~ 4 * V, so O(V^3)
  
## Timeline:
* Week 1 (March 28 - April 03): Data preprocessing
* Week 2 (April 04 - April 10): Transform the images to the graphs described above.
* Week 3 (April 11 - April 17): Implement our graphs algorithms (likely Dinic’s)
* Week 4 (April 17 - April 23): Implement our graphs algorithms (likey Edmond Karps)
* Week 4 (April 23 - April 29): Make a TUI for users to input the background seeds and foreground seeds. 
* Week 5 (April 30 - May 06): Work on the final presentation + final written proposal.



          
