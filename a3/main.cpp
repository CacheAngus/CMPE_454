/* A basic raytracer
 *
 * You can move the viewpoint with the left mouse button, and
 * zoom with the middle mouse button.  With the mouse in the
 * window, you can press '?' to see the options.
 *
 * Whenever nothing is happening in the window, the program starts
 * raytracing the current scene, and draws that as soon as it's done.
 * You can move the viewpoint again, or press a button, and it'll
 * start raytracing again from the new position.
 */


#include "headers.h"

#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include "rtWindow.h"
#include "scene.h"
#include "material.h"
#include "seq.h"
#include "gpuProgram.h"
#include "font.h"



Scene      *scene;
RTwindow   *win;
GPUProgram *gpuProg;

char *filename[2] = { NULL, NULL }; // from command line


void skipComments( istream &in );
void parseOptions( int argc, char **argv );


// Main program


int main( int argc, char **argv )

{
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " sceneFile ..." << endl;
    exit(1);
  }

  // Set up GLFW

  if (!glfwInit())
    return 1;

  glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_ES_API );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );

  // Set up the scene

  scene = new Scene();		// must exist before parseOptions() is called
  parseOptions( argc, argv );

  // win = new RTwindow( 20, 50, 1200, 800, filename[0], scene ); // production
  win = new RTwindow( 20, 50, 480, 320, filename[0], scene ); // debugging
  scene->setWindow( win );
  
  // gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );

  // Init fonts (must be done after the window is created, above)

#ifdef USE_FREETYPE
  initFont( "FreeSans.ttf", 20 ); // 20 = font height in pixels
#endif

  // Init GPU

  gpuProg = new GPUProgram( "wavefront.vert", "wavefront.frag" );

  // Read the scene file

  {
    ifstream in( filename[0] );

    if (!in) {
      cerr << "Error opening " << filename[0] << ".  Check that it exists and that the permissions are set to allow you to read it." << endl;
      exit(1);
    }

    char *basename = strdup(filename[0]);
    char *p = strrchr( basename, '/' );
    if (p != NULL)
      *p = '\0';

    scene->read( basename, in );
  }

  // Output the scene if a second filename is present on the command line

  if (filename[1] != NULL) {
    ofstream out( filename[1] );
    scene->write( out );
  }

  // Main loop

  int prevButtonDown = -1;

  while (!glfwWindowShouldClose( win->window )) {

    glfwPollEvents();

    if (win->redisplay) {
      win->display();
      glfwSwapBuffers( win->window );
    }

    scene->renderRT( win->redisplay ); // parameter == "start raytracing again if window is redisplayed"

    if (scene->stop && (scene->buttonDown == GLFW_MOUSE_BUTTON_MIDDLE || prevButtonDown != scene->buttonDown)) {
      mat4 WCS_to_VCS = lookat( win->eye, win->lookAt, win->upDir );
      mat4 VCS_to_CCS = perspective( win->fovy, win->windowWidth / win->windowHeight, win->zNear, win->zFar );
      scene->draw_RT_and_GL( gpuProg, WCS_to_VCS, VCS_to_CCS );
    }

    prevButtonDown = scene->buttonDown;

    win->redisplay = false;
  }

  // Clean up

  glfwDestroyWindow( win->window );
  glfwTerminate();

  return 0;
}



// Parse the command-line options

void parseOptions( int argc, char **argv )

{
  int next_fn = 0;
  
  while (argc > 1) {
    argv++;
    argc--;
    if (argv[0][0] != '-') {

      if (next_fn >= 2)
	cerr << "Only two filenames allowed on command line" << endl;
      else
	filename[ next_fn++ ] = argv[0];

    } else switch( argv[0][1] ) {

    case 'd':			// max depth for ray tracing
      argc--; argv++;
      scene->maxDepth = atoi( *argv );
      break;

    case 't':			// use texture maps?
      scene->useTextureTransparency = !scene->useTextureTransparency;
      break;

    case 'g':			// number of glossy iterations
      argc--; argv++;
      scene->glossyIterations = atoi( *argv );
      break;

    case 'm':			// use mipMaps?
      Texture::useMipMaps = !Texture::useMipMaps;
      break;

    default:
      cerr << "Unrecognized option -" << argv[0][1] << ".  Options are:" << endl;
      cerr << "  -d #   set max depth\n" << endl;
      cerr << "  -t     toggle texture transparency\n" << endl;
      break;
    }
  }

  if (next_fn == 0) {
    cerr << "No input filename provided on command line" << endl;
    abort();
  }
}


// Skip past a comment

int lineNum = 1;

void skipComments( istream &in )

{
  char c;

  // get next non-space

  do {
    in.get(c);
    if (c == '\n')
      lineNum++;
  } while (in && isspace(c));
  in.putback(c);

  // Skip past any comments

  while (c == '#') {
    do
      in.get(c);
    while (in && c != '\n');
    lineNum++;
    do {
      in.get(c);
      if (c == '\n')
	lineNum++;
    } while (in && isspace(c));
    in.putback(c);
  }
}
