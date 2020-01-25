// Missile defence game


#include "headers.h"


// Window and world dimensions

#define WINDOW_X_POS   100
#define WINDOW_Y_POS    50

#define WINDOW_WIDTH   600
#define WINDOW_HEIGHT  400

#define WORLD_LEFT   -0.02	// The world lives in a [0,1] x [0,1] box
#define WORLD_RIGHT   1.02	// with a small (0.02) border all around.
#define WORLD_BOTTOM -0.02
float worldTop;			// set in main()

// The "state" contains the world and manages all actions.

#include "state.h"

State *state;


// Error callback

void errorCallback( int error, const char* description )

{
  cerr << "Error " << error << ": " << description << endl;
  exit(1);
}


// Key callback

void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
  
{
  if (action == GLFW_PRESS)
    switch (key) {
      
    case GLFW_KEY_ESCAPE:	// ESC closes window
      glfwSetWindowShouldClose( window, GL_TRUE );
      break;
    }
}


// Mouse button callback

void mouseButtonCallback( GLFWwindow* window, int button, int action, int mods )

{
  if (action == GLFW_PRESS) {

    // Get mouse position
    
    double x, y;
    glfwGetCursorPos(window, &x, &y );

    // Calculate the world coordinates of mouse (x,y)

    float wx = x; // (wrong)
    float wy = y;

    // Shoot from silo 0, 1, or 2

    switch (button) {

    case GLFW_MOUSE_BUTTON_LEFT:
      state->fireMissile( 0, wx, wy );
      break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
      state->fireMissile( 1, wx, wy );
      break;

    case GLFW_MOUSE_BUTTON_RIGHT:
      state->fireMissile( 2, wx, wy );
      break;
    }
  }
}
 

// Main program

int main( int argc, char **argv )

{
  // Trap all errors (do this *before* creating the window)

  glfwSetErrorCallback( errorCallback );
  
  // Init everything

  GLFWwindow* window;

  if (!glfwInit())
    return 1;
  
  glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_ES_API );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );

  window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "Missile Defence", NULL, NULL);
  
  if (!window) {
    glfwTerminate();
    return 1;
  }

  glfwSetWindowPos( window, WINDOW_X_POS, WINDOW_Y_POS );

  glfwMakeContextCurrent( window );
  glfwSwapInterval( 1 );
  gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );

  // Callbacks

  glfwSetKeyCallback( window, keyCallback ); // key
  glfwSetMouseButtonCallback( window, mouseButtonCallback ); // mouse button 

  // Init world state

  worldTop = (WORLD_RIGHT - WORLD_LEFT) / (float) WINDOW_WIDTH * WINDOW_HEIGHT + WORLD_BOTTOM; // y coordinate at top of window

  state = new State( WORLD_LEFT, WORLD_RIGHT, WORLD_BOTTOM, worldTop );

  // Main loop

  struct timeb prevTime, thisTime; // record the last rendering time
  ftime( &prevTime );

  while (!glfwWindowShouldClose( window )) {

    // Find elapsed time since last render

    ftime( &thisTime );
    float elapsedSeconds = (thisTime.time + thisTime.millitm / 1000.0) - (prevTime.time + prevTime.millitm / 1000.0);
    prevTime = thisTime;

    // Update the world state

    state->updateState( elapsedSeconds );

    // Clear, display, and check for events

    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClear( GL_COLOR_BUFFER_BIT );

    state->draw();

    glfwSwapBuffers( window );

    glfwPollEvents();
  }

  // Clean up

  glfwDestroyWindow( window );
  glfwTerminate();

  return 0;
}
