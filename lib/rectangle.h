#ifndef RECTANGLE_H  
#define RECTANGLE_H  
  
using namespace std;

class Rectangle
{
  int x, y;
  public:
    void set_vals (long, long);
    void draw_ascii (int, int);
    void draw_image (int, int);
    int area () {
      return (x * y);
    }
};

#endif
