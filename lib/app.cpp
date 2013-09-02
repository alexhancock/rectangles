#include <iostream>
#include <fstream>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "util/util.hpp"
#include "util/shaders.hpp"

#include <GLUT/glut.h>
#include "math_3d.h"

GLuint VBO;
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
    Scale += 0.004f;
    glUniform1f(gScaleLocation, sinf(Scale));

    // Create a 4x4 matrix to perform a translation transformation
    Matrix4f World;
    World.m[0][0] = 1.0f; World.m[0][1] = 0.0f; World.m[0][2] = 0.0f; World.m[0][3] = sinf(Scale);
    World.m[1][0] = 0.0f; World.m[1][1] = 1.0f; World.m[1][2] = sinf(Scale); World.m[1][3] = sinf(Scale);
    World.m[2][0] = 0.0f; World.m[2][1] = 0.0f; World.m[2][2] = 1.0f; World.m[2][3] = 0.0f;
    World.m[3][0] = 0.0f; World.m[3][1] = sinf(Scale); World.m[3][2] = 0.0f; World.m[3][3] = 1.0f;

    // Load the matrix into the shader
    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World.m[0][0]);

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
    glutIdleFunc(RenderScene);
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

    glClearColor(0.3f, 0.5f, 1.0f, 0.0f);

    CreateVertexBuffer();
    SetupShaders();

    gScaleLocation = glGetUniformLocation(shaderProgram, "gScale");

    glutMainLoop();

    return 0;
}
