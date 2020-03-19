// arcballWindow.C


#include "arcballWindow.h"
#include <fstream>


using namespace std;


// Display everything after computing the WCS-to-VCS and VCS-to-CCS transforms

void arcballWindow::display()

{
  mat4 WCS_to_VCS = lookat( eye, lookAt, upDir );
  mat4 VCS_to_CCS = perspective( fovy, windowWidth / windowHeight, zNear, zFar );

  userDraw( WCS_to_VCS, VCS_to_CCS );
}



// Handle window size changes

void arcballWindow::windowSizeCallback( GLFWwindow* window, int width, int height )

{
  arcballWindow *w = (arcballWindow*) glfwGetWindowUserPointer( window );

  w->redisplay = true;

  w->windowWidth  = width;
  w->windowHeight = height;
  
  glViewport( 0, 0, width, height );
}


// Keypress callback

GLFWcursor* arcballWindow::rotationCursor;
GLFWcursor* arcballWindow::translationCursor;

void arcballWindow::keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )

{
  if (action != GLFW_PRESS)
    return;

  arcballWindow *w = (arcballWindow*) glfwGetWindowUserPointer( window );

  if (w->userKeyAction( key, scancode, action, mods ))
    return;

  // Handle event if not handled in derived class

  static int viewNum = 0; // number of the view to read or write
  char filename[1000];

  switch (key) {

  case ' ': // toggle mode between rotation and translation
    if (w->mode == ROTATE)
      w->mode = TRANSLATE;
    else
      w->mode = ROTATE;
    glfwSetCursor( window, (w->mode == TRANSLATE ? translationCursor : rotationCursor) );
    break;

  case '0': // set viewNum
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    viewNum = key - '0';
    break;

  case 'R': // read a view
    sprintf( filename, ".view%d", viewNum );
    w->readViewParams( filename );
    break;

  case 'W': // write a view
    sprintf( filename, ".view%d", viewNum );
    w->writeViewParams( filename );
    break;
  }
}


// Update viewing params based on new mouse position

void arcballWindow::mouseMotionCallback( GLFWwindow* window, double x, double y )

{
  arcballWindow *w = (arcballWindow*) glfwGetWindowUserPointer( window );

  w->mouseMoved = true;

  if (w->userMouseMotion( vec2( x, y ), w->buttonDown ))
    return;

  // Handle event if not handled in derived class

  vec3 xdir, ydir, zdir;

  ydir = w->upDir.normalize();
  zdir = (w->eye - w->lookAt).normalize();
  xdir = (ydir ^ zdir).normalize();

  if (w->mode == TRANSLATE) {

    if (w->buttonDown == GLFW_MOUSE_BUTTON_LEFT ) { // pan EYE AND WORLD in x and y

      w->lookAt = w->lookAt + 0.001 * w->fovy * ((w->mouse.x-x) * xdir + (y-w->mouse.y) * ydir);
      w->eye    = w->eye + 0.001 * w->fovy * ((w->mouse.x-x) * xdir + (y-w->mouse.y) * ydir);
      w->redisplay = true;

    } else if (w->buttonDown == GLFW_MOUSE_BUTTON_RIGHT) { // move ONLY THE EYE in z

      // w->lookAt = w->lookAt + (w->mouse.y-y)*0.02 * zdir;
      w->eye    = w->eye + (w->mouse.y-y)*0.02 * zdir;
      w->redisplay = true;
    }

  } else { // mode == ROTATE

    if (w->buttonDown == GLFW_MOUSE_BUTTON_RIGHT) { // zoom

      w->fovy *= 1.0 + 0.001*(w->mouse.y-y);
      if (w->fovy > 3*3.14159/2.0)
	w->fovy = 3*3.14159/2.0;
      if (w->fovy < 0.1)
	w->fovy = 0.1;
      w->redisplay = true;

    } else if (w->buttonDown == GLFW_MOUSE_BUTTON_LEFT) { // rotate

      mat4 WCS_to_VCS = lookat( w->eye, w->lookAt, w->upDir );
      mat4 VCS_to_WCS = WCS_to_VCS.inverse();
      mat4 T = VCS_to_WCS * w->arcballTransform( vec2(x,y), w->mouse ) * WCS_to_VCS;

      w->upDir = (T * vec4( w->upDir, 0 )).toVec3();
      vec3 eyeDir = w->eye - w->lookAt;
      w->eye = (T * vec4( eyeDir, 0)).toVec3() + w->lookAt;

      w->redisplay = true;
    }
  }

  w->mouse.x = x;
  w->mouse.y = y;
}


// Record button state when mouse button is pressed or released

void arcballWindow::mouseButtonCallback( GLFWwindow* window, int button, int action, int mods )

{
  arcballWindow *w = (arcballWindow*) glfwGetWindowUserPointer( window );

  if (action == GLFW_PRESS) {
    glfwSetCursorPosCallback( window, mouseMotionCallback );
    w->buttonDown = button;
  } else {
    glfwSetCursorPosCallback( window, NULL );
    w->buttonDown = -1;
  }

  double x, y;
  glfwGetCursorPos( window, &x, &y );

  if (w->userMouseAction( vec2( x, y ), button, action, mods ))
    return;

  w->redisplay = true;

  // Handle event if not handled in derived class

  if (action == GLFW_PRESS) {

    // store initial mouse position
      
    w->mouse.x = x;
    w->mouse.y = y;
    w->mouseMoved = false;

  } else { // (action == GLFW_RELEASE)

    // Check for unchanged position, in which case call the userMouseClick() function

    if (!w->mouseMoved)
      w->userMouseClick( vec2( x, y ), button );
  }
}


// Output the view parameters

void arcballWindow::writeViewParams( char * filename )

{
  ofstream out( filename );

  if (!out) { 
    cerr << "Error: Failed to open the output file\n";
  } else
    out << eye    << endl
	<< lookAt << endl
	<< upDir  << endl
	<< fovy   << endl
	<< zNear << ' ' << zFar << endl;
}


// Input the view parameters

void arcballWindow::readViewParams( char * filename )

{
  ifstream in( filename );

  if (!in) 
    cerr << "Error: Failed to open the input file\n";
  else
    in >> eye
       >> lookAt
       >> upDir
       >> fovy
       >> zNear >> zFar;
}


// Find 2d mouse position on 3D arcball

vec3 arcballWindow::arcballPos( vec2 pos )

{
  vec3 p(  pos.x/(float)windowWidth * 2 - 1, -(pos.y/(float)windowHeight * 2 - 1), 0 );
  float rr = p * p;
  if (rr <= 1)			// inside arcball
    p.z = sqrt( 1 - rr );
  else
    p = p.normalize();
  return p;
}


mat4 arcballWindow::arcballTransform( vec2 pos, vec2 prevPos )

{
  vec3 p1 = arcballPos( pos );
  vec3 p0 = arcballPos( prevPos );

  float dot = p0 * p1;
  if (dot > 1) dot=1;
  float angle = acos( dot );

  vec3 axis = p0 ^ p1;

  return rotate( -1 * angle, axis );
}


