// state.cpp


#include "headers.h"

#include "state.h"


// Draw each of the objects in the world
void State::draw() 

{
  int i;

  gpuProgram->activate();

  glUniformMatrix4fv( glGetUniformLocation( gpuProgram->id(), "M"), 1, GL_TRUE, &M[0][0] );

  silos[0].draw( gpuProgram );
  
  for (i=0; i<silos.size(); i++)
    silos[i].draw( gpuProgram );

  for (i=0; i<cities.size(); i++)
    cities[i].draw( gpuProgram );

  for (i=0; i<missilesIn.size(); i++)
    missilesIn[i].draw( gpuProgram );

  for (i=0; i<missilesOut.size(); i++)
    missilesOut[i].draw( gpuProgram );

  for (i=0; i<explosions.size(); i++)
    explosions[i].draw( gpuProgram );
    
  for( i=0; i<contractions.size(); i++)
    contractions[i].draw(gpuProgram);

  gpuProgram->deactivate();
}


// Update the state of the world after some time interval, deltaT

void State::updateState( float deltaT )

{
  int i;

  // Update the time

  currentTime += deltaT;

  // Generate some new missiles.  The rate of missile generation
  // should increase with time.

  if (randIn01()<0.01 + (currentTime * .0005)) {	// New missile 
    float a = randIn01();
    if (a < 0.5){
      a = -a;
    }
    missilesIn.add( Missile( vec3( randIn01(), worldTop, 0), // source
			     vec3( (0.02*a), -0.1, 0 ),         // velocity
			     0,                              // destination y
			     vec3( 1,1,0 ) ) );              // colour
  }

  // Look for terminating missiles

  for (i=0; i<missilesIn.size(); i++)
    if (missilesIn[i].hasReachedDestination()) {
      explosions.add(Circle(missilesIn[i].position(), 0.2, 0.05, vec3(1,.714,.757)));
      missilesIn.remove(i);
      i--;
    }

  for (i=0; i<missilesOut.size(); i++)
    if (missilesOut[i].hasReachedDestination()) {
      explosions.add(Circle(missilesOut[i].position(), 0.2, 0.05, vec3(1,0,1)));
      missilesOut.remove(i);
      i--;
    }

  // Look for terminating explosions

  for (i=0; i<explosions.size(); i++)
    if (explosions[i].radius() >= explosions[i].maxRadius()){
      for (int a = 0; a<silos.size(); a++){
          if((silos[a].position() - explosions[i].getPos()).length() <= explosions[i].radius()){
              silos.remove(a);
          }
      }
      for(int j =0; j<cities.size(); j++){
          if((cities[j].getPos() - explosions[i].getPos()).length() <=  explosions[i].radius()){
              cities.remove(j);
          }
      }
      // add to list of contracting explosions
      contractions.add(explosions[i]);
      explosions.remove(i); //remove from explosions
      i--;
    }
  
for (int k=0; k<contractions.size();k++){
  if(contractions[k].radius() <= 0)
	 contractions.remove(k);
 }

  for(i=0; i<missilesIn.size();i++){
    for(int j=0;j<missilesOut.size();j++){
      vec3 outPos = missilesOut[j].position();
      vec3 inPos = missilesIn[i].position();
      if((inPos - outPos).length() <= 0.05){
        explosions.add(Circle(missilesIn[i].position(), 0.2, 0.05, vec3(1,.5,0)));
        missilesIn.remove(i);
       	i--;
	    missilesOut.remove(j);
	    j--;
      }
    }
  }
  
  // ADD CODE HERE

  // Update all the moving objects

  for (i=0; i<missilesIn.size(); i++)
    missilesIn[i].move( deltaT );

  for (i=0; i<missilesOut.size(); i++)
    missilesOut[i].move( deltaT );

  for (i=0; i<explosions.size(); i++)
    explosions[i].expand( deltaT);
  for (i=0; i<contractions.size(); i++)
    contractions[i].contract(deltaT);
}


// Fire a missile

void State::fireMissile( int siloIndex, float x, float y )

{
  const float speed = 0.3;
    
  if (silos[siloIndex].canShoot()) {
    explosions.add(Circle(vec3(x, y, 0), 0.2, 0.02, vec3(1,0,0.25)));

    silos[siloIndex].decrMissiles();
    missilesOut.add( Missile( silos[siloIndex].position(),           // source
			      speed *(vec3(x,y,0)-silos[siloIndex].position()), // velocity
			      worldTop,		                     // destination y
			      vec3( 0,1,1 ) ) );                     // colour
  }
}



// Create the initial state of the world


void State::setupWorld()

{
  // Keep track of the time

  currentTime = 0;

  timeOfIncomingFlight = 6;	// 6 seconds for incoming missile to arrive

  // Seed the random number generator

#ifdef _WIN32
  srand( 12345 );
#else
  struct timeb t;
  ftime( &t );
  srand( t.time );
#endif

  // Silos are added in order left, middle, right so that they have
  // indices 0, 1, and 2 (respectively) in the "silos" array.

  silos.add(  Silo( vec3( 0.1, 0, 0 ) ) );
  silos.add(  Silo( vec3( 0.5, 0, 0 ) ) );
  silos.add(  Silo( vec3( 0.9, 0, 0 ) ) );

  // Cities on the left

  cities.add( City( vec3( 0.2, 0, 0 ) ) );
  cities.add( City( vec3( 0.3, 0, 0 ) ) );
  cities.add( City( vec3( 0.4, 0, 0 ) ) );

  // Cities on the right

  cities.add( City( vec3( 0.6, 0, 0 ) ) );
  cities.add( City( vec3( 0.7, 0, 0 ) ) );
  cities.add( City( vec3( 0.8, 0, 0 ) ) );
}
