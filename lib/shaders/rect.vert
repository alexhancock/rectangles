#version 120

attribute vec3 Position;

uniform float gScale;
uniform mat4 gWorld;

void main()
{
  gl_Position = gWorld * vec4(Position, 1.0);
}
