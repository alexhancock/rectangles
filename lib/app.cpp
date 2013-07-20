#include <iostream>
#include "rectangle.h"

#include <GLUT/glut.h>

using namespace std;

void display(){
}

int main(int argc, char** argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(1000,600);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Rectangles App");
  glutDisplayFunc(display);
  glutMainLoop();

  cout << "We're going to make a rectangle\n";
  Rectangle rect;

  long w;
  cout << "Please enter a width: ";
  cin >> w;

  long h;
  cout << "Please enter a height: ";
  cin >> h;

  cout << "The rectangle's dimensions are: " << h << " x " << w << "\n";
  rect.set_vals (w, h);

  cout << "The rectangle's area is: " << rect.area() << "\n";
  cout << "\n";

  rect.draw_ascii(w, h);

  return 0;
}
