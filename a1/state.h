// The state 


#ifndef STATE_H
#define STATE_H


#include "gpuProgram.h"
#include "linalg.h"

#include "seq.h"
#include "missile.h"
#include "silo.h"
#include "city.h"
#include "circle.h"


class State {

 public:

  State( float l, float r, float b, float t ) {

    gpuProgram = new GPUProgram( "a1.vert", "a1.frag" );
    worldTop = t;
    M = ortho( l, r, b, t, -1, 1 ); // use orthographic projection with l,r,t,b at window edges

    setupWorld();
  }

  void setupWorld();
  void draw();
  void fireMissile( int siloIndex, float x, float y );
  void updateState( float deltaT );

 private:

  GPUProgram *gpuProgram;

  float worldTop;               // world coord at top of screen
  mat4  M;                      // world-to-window transform
  float currentTime;            // current game time
  float timeOfIncomingFlight;   // time taken for incoming missile to reach bottom

  seq<Silo> silos;
  seq<City> cities;
  seq<Missile> missilesIn;
  seq<Missile> missilesOut;
  seq<Circle> explosions;
};


#endif
