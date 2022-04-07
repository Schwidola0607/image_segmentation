#include "./cs225/PNG.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace cs225;

void grayscale(PNG& image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }
}

int main(){
    //read from data
    std::vector<PNG> images;
    std::vector<std::string> folder_names = {"airplane", "automobile", "bird", "cat", "deer", "dog", "frog", "horse", "ship", "truck"};
    for(const std::string& folder : folder_names) {
        for(int i=0; i<10; ++i){
            images.push_back(PNG());
            std::stringstream s;
            s << std::setfill('0') << std::setw(4) << i+1;
            if(!images.back().readFromFile("data/"+folder+"/"+s.str()+".png")) return 1;
            grayscale(images.back());
        }
    }

    for(size_t i=0; i<images.size(); ++i){
        std::stringstream s;
        s << std::setfill('0') << std::setw(4) << i;
        if(!images[i].writeToFile("grayscale_images/"+s.str()+".png")) return 1;
    }
    return 0;
}