#include <iostream>
#include <fstream>
#include <string.h>

#include "util/util.hpp"
#include "util/shaders.hpp"

#include <GLUT/glut.h>
#include "math_3d.h"

GLuint VBO;

using namespace std;

static void SetupShaders()
{
  Shaders shaderUtil;
  GLuint shaderProgram = shaderUtil.compile("lib/shaders/rect.vert", "lib/shaders/rect.frag");
  glUseProgram(shaderProgram);
}

static void RenderScene()
{
    SetupShaders();

    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(0);
    glutSwapBuffers();
}

static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderScene);
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[] = {
      Vector3f(-1.0f, -1.0f, 0.0f),
      Vector3f(1.0f, -1.0f, 0.0f),
      Vector3f(1.0f, 1.0f, 0.0f),
      Vector3f(-1.0f, 1.0f, 0.0f)
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{
    // TODO - Abstract drawing logic into a class
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rectangles");

    InitializeGlutCallbacks();

    GLenum res = glewInit();
    if (res != GLEW_OK) {
      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }

    glClearColor(0.1f, 0.8f, 0.6f, 0.0f);

    CreateVertexBuffer();
    glutMainLoop();

    return 0;
}
