// a1 vertex shader
//
// Attribute 0 is position, which gets transformed by the 4x4 matrix M

#version 300 es


uniform mat4 M;

layout (location = 0) in vec3 vertPosition;


void main()

{
  gl_Position = M * vec4( vertPosition, 1 );
}
