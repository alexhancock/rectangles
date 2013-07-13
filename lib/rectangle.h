#ifndef RECTANGLE_H  
#define RECTANGLE_H  
  
using namespace std;

class Rectangle
{
  int x, y;
  public:
    void set_vals (long, long);
    int area () {
      return (x * y);
    }
};

#endif
