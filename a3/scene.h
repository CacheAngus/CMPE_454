/* scene.h
 */


#ifndef SCENE_H
#define SCENE_H


class RTwindow;


#include <iostream>
#include "seq.h"
#include "linalg.h"
#include "object.h"
#include "light.h"
#include "eye.h"
#include "material.h"
#include "axes.h"
#include "glverts.h"
#include "arrow.h"


class Scene {

  RTwindow *    win;		// rendering window

  Eye *         eye;		// viewpoint
  seq<Light *>  lights;		// all lights
  seq<Object *> objects;	// all objects

  vec3        Ia;		// ambient illumination

  vec3  llCorner, up, right;	// window parameters

  seq<vec3> storedPoints;

  Axes    *axes; 		// draw axes
  Arrow   *arrow;		// draw an arrow

  // rtImage rendering

  GLuint rtImageTexID;
  vec4 *rtImage;		// texture storing the raytraced image
  static char *vertShader, *fragShader;
  GPUProgram *gpu;

 public:

  vec2 mouse;
  int buttonDown;

  bool stop; // RT stopped

  bool storingRays;
  seq<vec3> storedRays;	// each pair of points is a ray
  seq<vec3> storedRayColours;

  seq<Texture*> textures;	// all textures
  seq<Material*> materials;	// all materials
  int maxDepth;			// ray tracing depth
  int glossyIterations;		// number of rays to send for glossy reflections
  bool useTextureTransparency;
  bool showAxes;
  bool showObjects;
  bool jitter;
  int numPixelSamples;
  bool debug;
  vec2 debugPixel;

  float sceneScale; // max dimension of scene's bounding box (used to scale the debbugging arrows)


  GLVerts *glverts; 		// draw some verts

  Scene() {
    Ia = vec3(0.1,0.1,0.1);
    maxDepth = 8;
    glossyIterations = 6;
    useTextureTransparency = true;
    storingRays = false;
    showAxes = false;
    showObjects = true;
    rtImage = NULL;
    rtImageTexID = 0;
    gpu = NULL;
    axes = NULL;
    glverts = NULL;
    arrow = NULL;
    stop = false;
    jitter = false;
    numPixelSamples = 1;
    debug = false;
    debugPixel = vec2(-1,-1);
    sceneScale = 1;
  }

  void setWindow( RTwindow * w )
    { win = w; }

  void renderRT( bool restart );
  void renderGL( mat4 &WCS_to_VCS, mat4 &VCS_to_CCS );
  void draw_RT_and_GL( GPUProgram *gpuProg, mat4 &WCS_to_VCS, mat4 &VCS_to_CCS );
  void showPixelZoom( vec2 mouse );
  void read( const char *basename, istream &in );
  void write( ostream &out );
  vec3 pixelColour( int x, int y );
  vec3 raytrace( vec3 &rayStart, vec3 &rayDir, int depth, int thisObjIndex, int thisObjPartIndex );
  vec3 calcIout( vec3 N, vec3 L, vec3 E, vec3 R,
		   vec3 Kd, vec3 Ks, float ns, vec3 In );
  bool findFirstObjectInt( vec3 rayStart, vec3 rayDir, int thisObjIndex, int thisObjPartIndex, 
			   vec3 &P, vec3 &N, vec3 &T, float &param, int &objIndex, int &objPartIndex, Material *&mat, int lightIndex );

  bool findRefractionDirection( vec3 &rayDir, vec3 &N, vec3 &refractionDir );

  void outputEye()
    { cout << *eye << endl; }

  void drawStoredRays( GPUProgram *gpuProg, mat4 &WCS_to_VCS, mat4 &VCS_to_CCS );
  void drawRTImage();
  char *statusMessage();
};


#endif
