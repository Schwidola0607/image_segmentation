# kwandou2-bz16-khoadp2-snyeh2
final project repo for bkms

# GitHub Organization
* `cs225/` - image manipulation library written by CS 225
* `data/` - initial, unprocessed subset of data taken from CIFAR-10
* `grayscale_images/` - processed subset of data taken from CIFAR-10
* `tests/` - test suite + related test files
* `util/` - utility library by CS 225 used in our main executable
* `dinics.cpp`, `dinics.h` - class that implements Dinic's algorithm
* `edmondkarps.cpp`, `edmondkarps.h` - class that implements Edmond-Karp's algorithm
* `graph.cpp`, `graph.h` - class that represents a given image as a flow graph
* `edge.h` - struct that represents a directional edge from one vertex in the graph to another
* `main.cpp` - main executable, takes in an input image + seeds and outputs the segmented image
* `preprocessing.cpp` - executable that was used to process the images in `data/`
* `results.md` - written report

# Running Instructions

### How to run the main executable
* Navigate to the base directory of this repository in the command line
* Run `make`
* Run `./main <input image filepath> <output image filepath>`
* Provide seed coordinates as directed by the executable
* The output should be saved where you specified in the initial command

### How to run the test suite
* Navigate to the base directory of this repository in the command line
* Run `make test`
* Run `./test`
* The test suite consists of 5 3x3 images used to test the two image segmentation algorithms.
