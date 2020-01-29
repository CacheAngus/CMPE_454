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

  int decrMissiles() {
    roundsLeft--;  
    return roundsLeft;
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
    
    /*vec3 *verts2 = new vec3[roundsLeft];
    verts2[0]= pos;
    for(int i=0; i<roundsLeft; i++)
      verts2[i+1] = vec3(0, 1, 0);
    gpuProgram->drawVertices( verts2, roundsLeft, GL_LINES, vec3(1,0.75, 0.87) );*/

    delete [] verts;
    //delete [] verts2;
  }
  

 private:

  int roundsLeft;
};
  

#endif
