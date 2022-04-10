## Week 1 (March 28 - April 3)

* **Goal:** Finish preprocessing on image dataset - accomplished
* **Tasks:**
  * Alexander - Uploaded CS225 image library to the repo. Made a .gitignore file for the repo.
  * Khoa - Wrote a Python script to download CIFAR-10 from https://github.com/knjcode/cifar2png and to select 10 images from each category randomly to reduce the size of the dataset. Saved the dataset in the data folder.
  * Brandon - Wrote a C++ script which used the CS225 image library to grayscale every image from the data folder and save them in a grayscale_data folder. Wrote a Makefile.
* **Problems:** None
* **Next week:** Since we successfully accomplished this week's goal without any issues, we will continue following our initial plan in the team proposal - this means we will begin transforming the images into graphs.

## Week 2 (April 4 - April 10)

* **Goal:** Build a graph out of a png image - accomplished  
  * Beginnings of transforming images to graphs and deciding how we want to implement it.
Khoa compiles papers and other repo's approaches based on some intricacies within our implementation.  
* **Task:** 
  * Command Line Interface -> input pixels
  * Makefile (Graph + Edge files)
  * Graph  
  * Added `.o`, `.d` files and `.objs` to `.gitignore`

* Split up the given tasks into roles
  * Khoa make use of the `OptionParser` class provided in `util/util.h` library from CS225 to make a simple CLI for user to input foreground and background seeds.
  * Shao-Min added the functionality within main to add seeds and changed the format within graph to make instantiating pngs more clearer and to make the overall code clearer. 
  * Brandon created the Graph class and the Edge class. The Graph class stores a PNG and creates a graph (implemented as an adjacency list with Edges) based on the inputted PNG. It can also add background and foreground seeds which will be used by the segmentation algorithms.

* **Problems:** None  
* **Next week:** Since we successfully accomplished this week's goal faster than expected, we decide to speed up our plan and is looking into Dinic's algorithm this week and hopefully be able to finish it earlier next week.  
* **Optional:** If we have time next week we might consider look into CMake and Catch framework next week.  
