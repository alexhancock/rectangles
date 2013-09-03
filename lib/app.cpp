#include <iostream>
#include <fstream>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "util/util.hpp"
#include "util/pipeline.hpp"
#include "util/shaders.hpp"

#include <GLUT/glut.h>
#include "math_3d.h"

GLuint VertexBuffer;
GLuint IndexBuffer;

GLuint shaderProgram;
GLuint gScaleLocation;
GLuint gWorldLocation;

using namespace std;

static void SetupShaders()
{
  Shaders shaderUtil;
  shaderProgram = shaderUtil.compile("lib/shaders/rect.vert", "lib/shaders/rect.frag");
  glUseProgram(shaderProgram);
}

static void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    static float Scale = 0.0f;
    Scale += 0.002f;
   
    Pipeline p;
    p.Scale(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f));
    p.WorldPos(sinf(Scale) * 0.5f, 0.0f, 0.0f);
    p.Rotate(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f);

    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (const GLfloat *)p.GetTrans());

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glutSwapBuffers();
}

static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderScene);
    glutIdleFunc(RenderScene);
}

static void CreateVertexBuffer()
{
    Vector3f Vertices[] = {
      Vector3f(-1.0f, -1.0f, 0.0f),
      Vector3f(0.0f, -1.0f, 1.0f),
      Vector3f(1.0f, -1.0f, 0.0f),
      Vector3f(0.0f, 0.5f, 0.0f)
    };

    glGenBuffers(1, &VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    unsigned int Indices[] = {
      0, 3, 1,
      1, 3, 2,
      2, 3, 0,
      0, 1, 2
    };

    glGenBuffers(1, &IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{
    // TODO - Abstract drawing logic into a class
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Rectangles");

    InitializeGlutCallbacks();

    GLenum res = glewInit();
    if (res != GLEW_OK) {
      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    CreateVertexBuffer();
    SetupShaders();

    gScaleLocation = glGetUniformLocation(shaderProgram, "gScale");

    glutMainLoop();

    return 0;
}
