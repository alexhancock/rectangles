#include <iostream>
#include "rectangle.h"

void Rectangle::set_vals(long a, long b) {
  x = a;
  y = b;
}

void Rectangle::draw_ascii(int width, int height) {
  for (int h = 0; h < height; h++){
    for (int w = 0; w < width; w++){
      cout << "+";
      if (w == width-1) cout << "\n";
    }
  }
}

void Rectangle::draw_image(int width, int height) {
  // TODO
}
