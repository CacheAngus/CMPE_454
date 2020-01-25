// Circle class


#ifndef CIRCLE_H
#define CIRCLE_H


#include "headers.h"
#include "gpuProgram.h"


class Circle {
 public:

  // Constructors

  Circle() {}

  Circle( vec3 p, float s, float maxRad, vec3 c ) {
    pos = p;
    r = 0;
    maxR = maxRad;
    speed = s;
    colour = c;
  }

  // Draw the circle

  void draw( GPUProgram *gpuProgram ) {

    const int NUM_SEGMENTS = 90; // number of pieces of circle perimeter

    vec3 *verts = new vec3[NUM_SEGMENTS+1];

    verts[0] = pos;
    
    for (int i=0; i<NUM_SEGMENTS; i++) {
      float theta = (i/(float)(NUM_SEGMENTS-1)) * (2*M_PI);
      verts[i+1] = vec3( pos.x + r * sin(theta), pos.y + r * cos(theta), 0 );
    }

    gpuProgram->drawVertices( verts, NUM_SEGMENTS, GL_TRIANGLE_FAN, colour );

    delete [] verts;
  }

  // Expand the circle over a time interval, deltaT

  void expand( float deltaT ) {
    r = r + deltaT * speed;
  }

  // Return the current and max radii

  float radius() {
    return r;
  }

  float maxRadius() {
    return maxR;
  }

 private:

  GLuint VAO;
  
  vec3  pos;			// centre
  float r;			// current radius
  float maxR;			// maximum radius
  float speed;			// speed at which radius increases
  vec3  colour;		// colour of circle
};


#endif
