/* arcballWindow.h
 *
 * Creates a window with mouse-based viewpoint manipulation.
 *
 * Derived class must provide a draw() routine.
 */


#ifndef ARCBALL_WINDOW_H
#define ARCBALL_WINDOW_H

#include "headers.h"


typedef enum { TRANSLATE, ROTATE } ModeType;


class arcballWindow {

  vec2     mouse;		// last mouse position
  ModeType mode;		// translate or rotate mode
  int      buttonDown;		// mouse button currently held down

  vec3 arcballPos( vec2 pos );
  mat4 arcballTransform( vec2 pos, vec2 prevPos );

  static GLFWcursor* rotationCursor;
  static GLFWcursor* translationCursor;

  static void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
  static void mouseButtonCallback( GLFWwindow* window, int button, int action, int mods );
  static void mouseMotionCallback( GLFWwindow* window, double x, double y );
  static void windowSizeCallback( GLFWwindow* window, int width, int height );

 public:

  GLFWwindow* window;
  bool        redisplay;
  bool        mouseMoved; 

  float fovy;			// field of view in y
  vec3  eye, upDir, lookAt;	// viewing parameters
  float zNear, zFar;		// near/far clipping planes

  float windowWidth, windowHeight;

  arcballWindow( int x, int y, int width, int height, const char *title ) {

    glfwWindowHint( GLFW_ALPHA_BITS, 8 );

    window = glfwCreateWindow( width, height, title, NULL, NULL);
  
    if (!window) {
      glfwTerminate();
      exit(1);
    }

    glfwSetWindowPos( window, x, y );

    glfwMakeContextCurrent( window );
    glfwSwapInterval( 1 );

    gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );

    glfwSetKeyCallback(         window, keyCallback );
    glfwSetMouseButtonCallback( window, mouseButtonCallback );
    glfwSetCursorPosCallback(   window, NULL );
    glfwSetWindowSizeCallback(  window, windowSizeCallback );

    glfwSetWindowUserPointer( window, (void*) this ); // window stores pointer to this instance of 'arcballWindow'  

    rotationCursor = glfwCreateStandardCursor( GLFW_ARROW_CURSOR );
    translationCursor = glfwCreateStandardCursor( GLFW_CROSSHAIR_CURSOR );

    windowWidth = width;
    windowHeight = height;

    mode      = ROTATE;
    zNear     = 1;
    zFar      = 1000;
    redisplay = true;
  }

  void display();
  void writeViewParams( char * filename );
  void readViewParams( char * filename );

  // userDraw() must be provided in the derived class
  
  virtual void userDraw( mat4 &WCS_to_VCS, mat4 &VCS_to_CCS ) = 0;

  // The following functions can be provided in the derived class.
  // These are called before the corresponding arcballWindow functions
  // are executed.  But, if these functions return 'true', the
  // corresponding arcballWindow functions will NOT be executed.
  
  virtual bool userKeyAction( int key, int scancode, int action, int mods ) { return false; }
  virtual bool userMouseAction( vec2 mousePos, int button, int action, int mods )          { return false; }
  virtual bool userMouseMotion( vec2 mousePos, int button )                 { return false; }
  virtual bool userMouseClick( vec2 mousePos, int button )                  { return false; }
};

#endif

