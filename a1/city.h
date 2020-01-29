// A city


#ifndef CITY_H
#define CITY_H


#include "headers.h"
#include "gpuProgram.h"
#include "buildings.h"


class City : public Building {
 public:

  // Constructors 

  City() {}

  City( vec3 pos ) : Building( pos ) {
   p = pos;
}

  // Draw the city

  void draw( GPUProgram *gpuProgram ) {

    vec3 verts[4] = {
      vec3( pos.x + .04, pos.y,       0 ),
      vec3( pos.x + .04, pos.y + .03, 0 ),
      vec3( pos.x - .04, pos.y + .03, 0 ),
      vec3( pos.x - .04, pos.y,       0 )
    };

    gpuProgram->drawVertices( &verts[0], 4, GL_LINE_LOOP, vec3(1,1,1) );
  }

  bool isHit( vec3 missilePos, float radius); 
  
 vec3 getPos(){
	return p;
 }

 private:
 
  vec3 p;
};

  


#endif
