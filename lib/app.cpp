#include <iostream>
#include "rectangle.h"

#include <GL/glew.h>
#include <GLUT/glut.h>

#include "math_3d.h"

using namespace std;

void display(){
  glClear(GL_COLOR_BUFFER_BIT);

  // Spin up glew
  GLenum res = glewInit();
  if (res != GLEW_OK)
  {
    fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
    return;
  }

  Vector3f Vertices[1];
  Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);
  
  GLuint VBO;
  glGenBuffers(1, &VBO);

  // Set up the buffer to hold an array of vertices
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

  // Enable the vertex attr, so that it's data is available to the rendering pipeline
  glEnableVertexAttribArray(0);
  
  // Bind our data to the buffer, so we can draw it
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // Tell the buffer how to interpret data
 
  // 1st arg - position of attr in Vertices
  // 2nd - Number of components in the attribute - three for x, y, z
  // 3rd - data type of components
  // 4th - whether or not to normalize data before used in the pipeline
  // 5th - The "stride" or number of bytes between two instances of the attr in the buffer
  // 6th - not useful here, but you can use it to supply a bit offset for position/normals
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  // Draw! - This is a simple ordered draw call, with no index buffer
  // 1st arg - specifies the topology as points so every vertex is one points
  // 2nd - where to start pulling data 
  // 3rd - how many to draw (just our one point for now)
  glDrawArrays(GL_POINTS, 0, 1);

  // Disable the vertex attr
  glDisableVertexAttribArray(0);
  
  // Switch the offscreen buffer we've been drawing into to the front, so it displays on the window
  glutSwapBuffers();
}

int main(int argc, char** argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(900, 500);
  glutInitWindowPosition(100, 50);
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
