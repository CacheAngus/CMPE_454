// a1 fragment shader

#version 300 es

uniform mediump vec3 colour;

out mediump vec4 fragColour;


void main()

{
  fragColour = vec4( colour, 1.0 );
}
