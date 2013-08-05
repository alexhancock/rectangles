#ifndef SHADERS_H
#define SHADERS_H

#include <iostream>
#include <fstream>
#include <string.h>

#include <GL/glew.h>
#include <GLUT/glut.h>

using namespace std;

class Shaders {
  public:
    GLuint compile (const char *path, const char *frag);
};

#endif
