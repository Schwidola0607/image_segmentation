#include <iostream>
#include "util/util.h"
#include "cs225/PNG.h"
#include <string>
#include <vector>
#include <algorithm>

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
  cout << "When finish type -1 -1" << endl;
  vector <pair <int, int>> foreground_coordinates;
  while (true) {
    int x, y;
    cin >> x >> y;
    if (x == -1 && y == -1) {
      break;
    }
    if (x >= (int)png.width() || y >= (int)png.height() || x < 0 || y < 0) {
      cout << "Ignore out of bound coordinate" << endl;
      continue;
    }
    foreground_coordinates.push_back({x, y});  
  }
  
  cout << "Please type in background seeds as 2d coordinates" << endl;
  cout << "When finish type -1 -1" << endl;
  vector <pair <int, int>> background_coordinates;
  while (true) {
    int x, y;
    cin >> x >> y;
    if (x == -1 && y == -1) {
      break;
    }
    if (x >= (int)png.width() || y >= (int)png.height() || x < 0 || y < 0) {
      cout << "Ignore out of bound coordinate" << endl;
      continue;
    }
    background_coordinates.push_back({x, y});  
  }
}