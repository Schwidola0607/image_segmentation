# kwandou2-bz16-khoadp2-snyeh2
Final project repo for bkms. We implemented 2 flow algorithms and a OpenCV prompt for users to select foreground and background seeds. More instructions can be found below.

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

# Setup instructions

# Running Instructions
### How to run the openCV prompt window
* Dependencies: `python3`, `opencv`
* Run `python3 SeedGenerator.py`.
* Input the file path to the image you want to segment
* A window will pop up asking you to click on foreground seeds. After that press `Esc`.
* Same window will now ask you to click on background seeds. After that press `Esc`.
* An `input.txt` file will be created and the seeded image will appear in the `Output` folder.

### How to run the main executable
* Navigate to the base directory of this repository in the command line.
* Run `make`.
* Run `./main`.
* Main will automatically read from `input.txt` to get the foreground and background seeds and run Dinics and Edmond-Karps on the seeded image.
* The output of running the Dinics and Edmond-Karps algorithm will be saved in the `Output` folder.

### Alternative running instructions:
* run `sh -e run.sh` (untested in ews environment).

### How to run the test suite
* Navigate to the base directory of this repository in the command line.
* Run `make test`.
* Run `./test`.
* The test suite consists of 5 3x3 images used to test the two image segmentation algorithms.

# Credits
* Khoa Pham
* Brandon Zhang
* Shao-Min Yeh
* William Kwandou
