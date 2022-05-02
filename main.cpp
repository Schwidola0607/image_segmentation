#include <iostream>
#include "util/util.h"
#include "cs225/PNG.h"
#include "Algorithms/edmondkarps.h"
#include "Algorithms/dinics.h"
#include "Graph/graph.h"
#include <string>
#include <set>
#include <algorithm>

using namespace util;
using namespace cs225;
using namespace std;
// namespace opts
// {
//   bool help = false;
// }


int main() { // int args, const char** argv
  string inFile;
  PNG png;

  // string outFile;
  // string FlowAlgorithm = "-d";  
  // OptionsParser optparser;
  // optparser.addArg(inFile);
  // optparser.addArg(outFile);
  // optparser.addArg(FlowAlgorithm);
  // optparser.addOption("help", opts::help);
  // optparser.addOption("h", opts::help);
  // optparser.parse(args, argv);

  // if (opts::help) {
  //   cout << "Usage: " << argv[0]
  //         << " image to perform segmentation "
  //           "[input_image.png] [output_image.png] [flow algorithm]"
  //         << endl;
  //   return 0;
  // }
  // if (inFile == "") {
  //   cout << "Please specify input image" << endl;
  //   return 1;
  // }
  // if (outFile == "") {
  //   cout << "Please specify output image" << endl;
  //   return 1;
  // }
  // if (FlowAlgorithm == "") {
  //   cout << "Default flow algorithm: Dinics" << endl;
  // }
  // png.readFromFile(inFile);
  
  /**
   * @brief Un comment the below code if Open-CV does not work on your machine
   * It will act as a CLI to for users to manually input code in
   */
  // cout << "Please type in foreground seeds as 2d coordinates" << endl;
  // cout << "When finished, type -1 -1" << endl;
  // set<pair<int, int>> foreground_seeds;
  // while (true) {
  //   int x, y;
  //   cin >> x >> y;
  //   if (x == -1 && y == -1) {
  //     break;
  //   }
  //   if (x >= (int)png.width() || y >= (int)png.height() || x < 0 || y < 0) {
  //     cout << "Ignore out of bounds coordinates" << endl;
  //     continue;
  //   }
  //   foreground_seeds.insert({x,y});  
  // }
  
  // cout << "Please type in background seeds as 2d coordinates" << endl;
  // cout << "When finished, type -1 -1" << endl;
  // set<pair<int, int>> background_seeds;
  // while (true) {
  //   int x, y;
  //   cin >> x >> y;
  //   if (x == -1 && y == -1) {
  //     break;
  //   }
  //   if (x >= (int)png.width() || y >= (int)png.height() || x < 0 || y < 0) {
  //     cout << "Ignore out of bounds coordinates" << endl;
  //     continue;
  //   }
  //   background_seeds.insert({x, y});  
  // }
  
  // Initialize set to store foreground and background seeds
  set<pair<int, int>> foreground_seeds;
  set<pair<int, int>> background_seeds;

  cout << "Reading in from input.txt" << endl;
  ifstream file("input.txt");

  // Obtain the image file path from input.txt
  cout << "Reading image file..." << endl;
  file >> inFile;
  png.readFromFile(inFile);

  // Obtain the foreground seeds from input.txt
  cout << "Reading in foreground seeds..." << endl;
  while (true) {
    int x, y;
    file >> x >> y;
    if (x == -1 && y == -1) {
      // Done reading in foreground seeds
      break;
    }
    if (x >= (int)png.width() || y >= (int)png.height() || x < 0 || y < 0) {
      cout << "Ignore out of bounds coordinate" << endl;
      continue;
    }
    foreground_seeds.insert({x, y});
  }

  // Obtain the background seeds from input.txt
  cout << "Reading in background seeds..." << endl;
  while (true) {
    int x, y;
    file >> x >> y;
    if (x == -1 && y == -1) {
      // Done reading in background seeds
      break;
    }
    if (x >= (int)png.width() || y >= (int)png.height() || x < 0 || y < 0) {
      cout << "Ignore out of bounds coordinate" << endl;
      continue;
    }
    background_seeds.insert({x, y});
  }
  // Close file from reading
  file.close();

  // Initialize a graph with foreground and background seeds
  Graph graph(inFile);
  for (const pair<int,int>& p : foreground_seeds) { graph.AddFSeed(p.first, p.second); } 
  for (const pair<int,int>& p : background_seeds) { graph.AddBSeed(p.first, p.second); }

  // Run Dinics and Edmond Karps on the graph to produce a segmented image
  vector <pair <int, int>> bg_pixels;
  // Run Dinics Algorithm on the seeded image
  Dinics dinic(&graph);
  long long max_flow_dinics = dinic.maxFlow();
  bg_pixels = dinic.getBackground();
  PNG segmented_png_dinics = graph.drawLine(bg_pixels);  
  segmented_png_dinics.writeToFile("Output/dinics.png");
  
  // Run Edmond-Karps Algorithm on the seeded image
  EdmondKarps ekarp(&graph);
  long long max_flow_ekarp = ekarp.maxFlow();
  bg_pixels = ekarp.getBackground();
  PNG segmented_png_ekarp = graph.drawLine(bg_pixels);  
  segmented_png_ekarp.writeToFile("Output/edmond-karps.png");
  
  cout << "Writing results of Dinics and Edmond-Karps to the Output folder" << endl;
}