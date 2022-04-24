#include <iostream>
#include "util/util.h"
#include "cs225/PNG.h"
#include "graph.h"
#include <string>
#include <set>
#include <algorithm>
#include "edmondkarps.h"

using namespace util;
using namespace cs225;
using namespace std;
namespace opts
{
  bool help = false;
}

int main(int args, const char** argv) {
  string inFile;
  string outFile;
  OptionsParser optparser;
  optparser.addArg(inFile);
  optparser.addArg(outFile);
  optparser.addOption("help", opts::help);
  optparser.addOption("h", opts::help);
  optparser.parse(args, argv);

  if (opts::help) {
    cout << "Usage: " << argv[0]
          << " image to perform segmentation "
            "[input_image.png] [output_image.png]"
          << endl;
    return 0;
  }
  if (inFile == "") {
    cout << "Please specify input image" << endl;
    return 1;
  }
  if (outFile == "") {
    cout << "Please specify output image" << endl;
    return 1;
  }
  PNG png;
  png.readFromFile(inFile);
  cout << "Please type in foreground seeds as 2d coordinates" << endl;
  cout << "When finished, type -1 -1" << endl;
  set<pair<int, int>> foreground_coordinates;
  while (true) {
    int x, y;
    cin >> x >> y;
    if (x == -1 && y == -1) {
      break;
    }
    if (x >= (int)png.width() || y >= (int)png.height() || x < 0 || y < 0) {
      cout << "Ignore out of bounds coordinates" << endl;
      continue;
    }
    foreground_coordinates.insert({x,y});  
  }
  
  cout << "Please type in background seeds as 2d coordinates" << endl;
  cout << "When finished, type -1 -1" << endl;
  set<pair<int, int>> background_coordinates;
  while (true) {
    int x, y;
    cin >> x >> y;
    if (x == -1 && y == -1) {
      break;
    }
    if (x >= (int)png.width() || y >= (int)png.height() || x < 0 || y < 0) {
      cout << "Ignore out of bounds coordinates" << endl;
      continue;
    }
    background_coordinates.insert({x, y});  
  }
  Graph graph(inFile);

  for (const pair<int,int>& p : foreground_coordinates) { graph.AddFSeed(p.first, p.second); } 
  for (const pair<int,int>& p : background_coordinates) { graph.AddBSeed(p.first, p.second); }

  EdmondKarps ek(&graph);
  cout << ek.maxFlow() << '\n';
  vector <pair<int, int>> bruh;
  for(int i=0; i<32; i++) {
    bruh.push_back(pair<int, int>(i, 2));
  }
  // ek.getBackground();
  PNG imageSeg = graph.draw(bruh);
  imageSeg.writeToFile(outFile);


}