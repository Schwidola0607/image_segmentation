# kwandou2-bz16-khoadp2-snyeh2
Final project repo for bkms. We implemented 2 flow algorithms and a OpenCV prompt for users to select foreground and background seeds. More instructions can be found below.

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

# Setup instructions

# Running Instructions
### How to run the openCV prompt window
* Run `python3 SeedGenerator.py`.
* A window will pop up asking you to click on foreground seeds. After that press `Esc`.
* Same window will now ask you to click on background seeds. After that press `Esc`.
* A seeded image along with a `input.txt` file will be created.
### How to run the main executable
* Navigate to the base directory of this repository in the command line.
* Run `make`.
* Run `./main <input image filepath> <output image filepath>`.
* Main will automatically read from `input.txt` to get the foreground and background seeds.
* The output should be saved where you specified in the initial command.

### Alternative running instructions:
* run `sh -e run.sh` (untested in ews environment).

### How to run the test suite
* Navigate to the base directory of this repository in the command line.
* Run `make test`.
* Run `./test`.
* The test suite consists of 5 3x3 images used to test the two image segmentation algorithms.
