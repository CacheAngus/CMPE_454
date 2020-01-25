// A Silo


#ifndef SILO_H
#define SILO_H

#include "headers.h"
#include "gpuProgram.h"
#include "buildings.h"


class Silo : public Building {
 public:

  // Constructors 

  Silo() {}

  Silo( vec3 pos ) : Building( pos ) {

    roundsLeft = 15;
  }

  bool canShoot() {
    return (roundsLeft > 0);
  }

  void decrMissiles() {
    roundsLeft--;
  }

  vec3 position() {
    return pos;
  }

  // Draw the silo

  void draw( GPUProgram *gpuProgram ) {

    const int NUM_SEGMENTS = 45; // number of pieces of hemisphere perimeter

    vec3 *verts = new vec3[NUM_SEGMENTS+1];

    verts[0] = pos;
    
    for (int i=0; i<NUM_SEGMENTS; i++) {
      float theta = (i/(float)(NUM_SEGMENTS-1)) * M_PI;
      verts[i+1] = vec3( pos.x + 0.04 * cos(theta), pos.y + 0.04 * sin(theta), 0 );
    }

    gpuProgram->drawVertices( verts, NUM_SEGMENTS+1, GL_TRIANGLE_FAN, vec3(1,1,1) );

    delete [] verts;
  }

 private:

  int roundsLeft;
};
  

#endif
