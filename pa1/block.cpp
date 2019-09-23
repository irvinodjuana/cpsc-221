#include "block.h"
 
/**
* Returns the width of the block.
*/
int Block::width() const{/*your code here*/
   if (data.size() == 0) return 0;
   return data[0].size();
}
 
/**
* Returns the height of the block.
*/
int Block::height() const{/*your code here*/
   return data.size();
}
 
/**
* Default Block constructor.
*/
Block::Block() {/* nothing */}
 
/**
* Useful Block constructor.
* Makes a block from the rectangle of width by height pixels in im
* whose upper-left corner is at position (x,y).
*/
Block::Block(PNG & im, int x, int y, int width, int height) {/*your code here*/
   for (int row = 0; row < height; row++) {
       data.push_back(vector<HSLAPixel>());
       for (int col = 0; col < width; col++) {
           data[row].push_back(*im.getPixel(x + col, y + row));
       }
   }
}
 
/**
* Draws the block at position (x,y) in the image im
*/
void Block::render(PNG & im, int x, int y) const {/*your code here*/
   for (int row = 0; row < height(); row++) {
       for (int col = 0; col < width(); col++) {
           *im.getPixel(x + col, y + row) = data[row][col];
       }
   }
}

/**
* Changes the saturation of every pixel in the block to 0,
* which removes the color, leaving grey.
*/
void Block::greyscale() {/*your code here*/
   for (int row = 0; row < height(); row++) {
       for (int col = 0; col < width(); col++) {
           data[row][col].s = 0;
       }
   }
}
 
