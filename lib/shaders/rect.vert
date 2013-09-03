#version 120

attribute vec3 Position;

varying vec4 Color;

uniform float gScale;
uniform mat4 gWorld;

void main()
{
  gl_Position = gWorld * vec4(Position, 1.0);
  Color = vec4(clamp(Position, 0.0, 0.5), 1.0);
}
