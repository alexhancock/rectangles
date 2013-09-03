#include <iostream>
#include <fstream>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "util/util.hpp"
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
    Scale += 0.01f;
    
    Matrix4f World;
    World.m[0][0] = cosf(Scale); World.m[0][1] = 0.0f; World.m[0][2] = -sinf(Scale); World.m[0][3] = 0.0f;
    World.m[1][0] = 0.0;         World.m[1][1] = 1.0f; World.m[1][2] = 0.0f        ; World.m[1][3] = 0.0f;
    World.m[2][0] = sinf(Scale); World.m[2][1] = 0.0f; World.m[2][2] = cosf(Scale) ; World.m[2][3] = 0.0f;
    World.m[3][0] = 0.0f;        World.m[3][1] = 0.0f; World.m[3][2] = 0.0f        ; World.m[3][3] = 1.0f;

    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World.m[0][0]);

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

    glClearColor(0.3f, 0.5f, 1.0f, 0.0f);

    CreateVertexBuffer();
    SetupShaders();

    gScaleLocation = glGetUniformLocation(shaderProgram, "gScale");

    glutMainLoop();

    return 0;
}
