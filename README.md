# kwandou2-bz16-khoadp2-snyeh2
Final project repo for bkms. We implemented 2 flow algorithms and a OpenCV prompt for users to select foreground and background seeds. More instructions can be found below.

# Project Overview

Image segmentation has novel applications in many fields, most notably in automated driving, which needs to find distinct features while driving (i.e. people, signs, traffic lights, street markings, etc). With this, we utilized various network flow algorithms, particularly Dinic's and Edmond-Karp's algorithms, to achieve this image segmentation. More specifically, we will use our network flow algorithms to divide small greyscale images into their foreground and background, which will partition an image into regions based on distinctive features. 

### Project Deliverables

* [Video Link](https://drive.google.com/file/d/1WAbGxi_hMabwwfRPrT-8GOaEE79-zblx/view?usp=sharing)
* [Project Report](https://github-dev.cs.illinois.edu/cs225-sp22/kwandou2-bz16-khoadp2-snyeh2/blob/main/md_files/results.md)

# GitHub Organization
* `Algorithms/` - Contains the classes that implement our two flow algorithms
* `Graph/` - Contains the classes that make up our graph representation of an image
* `Output/` - Contains output images from the main executable as well as the seed generator
* `cs225/` - Image manipulation library written by CS 225
* `images/` - Processed subset of images from the CIFAR-10 dataset (https://www.cs.toronto.edu/~kriz/cifar.html)
* `md_files/` - Contains our team contract, team proposal, weekly log, and results document
* `tests/` - Contains our test suite + related test files
* `util/` - Utility library by CS 225 used in our main executable
* `SeedGenerator.py` - Prompts the user with a GUI to pick foreground and background seeds on an image
* `main.cpp` - Takes seeds from the seed generator and runs both flow algorithms on the image to get the foreground/background
* `preprocessing.cpp` - Executable used to grayscale the images from CIFAR-10

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
