# Image Segmentation
Repository for our CS 225 Final Project

# Project Overview

Image segmentation has novel applications in many fields, most notably in automated driving, which needs to find distinct features while driving (i.e. people, signs, traffic lights, street markings, etc). With this, we utilized various network flow algorithms, particularly Dinic's and Edmond-Karp's algorithms, to achieve this image segmentation. More specifically, we will use our network flow algorithms to divide small greyscale images into their foreground and background, which will partition an image into regions based on distinctive features. 

# GitHub Organization
* `cs225/` - image manipulation library written by CS 225
* `grayscale_images/` - processed subset of data taken from the CIFAR-10 dataset (https://www.cs.toronto.edu/~kriz/cifar.html)
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

# Credits
* Khoa Pham
* Brandon Zhang
* Shao-Min Yeh
* William Kwandou
