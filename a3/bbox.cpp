/* bbox.C
 */


#include "headers.h"
#include "bbox.h"
#include "glverts.h"
#include "main.h"


void BBox::renderGL( mat4 &WCS_to_CCS ) 

{
  seq<vec3> pts;

  pts.add( vec3(min.x, min.y, min.z) );
  pts.add( vec3(min.x, min.y, max.z) );
  pts.add( vec3(min.x, max.y, min.z) );
  pts.add( vec3(min.x, max.y, max.z) );
  pts.add( vec3(max.x, min.y, min.z) );
  pts.add( vec3(max.x, min.y, max.z) );
  pts.add( vec3(max.x, max.y, min.z) );
  pts.add( vec3(max.x, max.y, max.z) );
  pts.add( vec3(min.x, min.y, min.z) );
  pts.add( vec3(max.x, min.y, min.z) );
  pts.add( vec3(min.x, min.y, max.z) );
  pts.add( vec3(max.x, min.y, max.z) );
  pts.add( vec3(min.x, max.y, min.z) );
  pts.add( vec3(max.x, max.y, min.z) );
  pts.add( vec3(min.x, max.y, max.z) );
  pts.add( vec3(max.x, max.y, max.z) );
  pts.add( vec3(min.x, min.y, min.z) );
  pts.add( vec3(min.x, max.y, min.z) );
  pts.add( vec3(min.x, min.y, max.z) );
  pts.add( vec3(min.x, max.y, max.z) );
  pts.add( vec3(max.x, min.y, min.z) );
  pts.add( vec3(max.x, max.y, min.z) );
  pts.add( vec3(max.x, min.y, max.z) );
  pts.add( vec3(max.x, max.y, max.z) );

  scene->glverts->draw( pts, vec3(0.5,0.5,0.5), GL_LINES, WCS_to_CCS );
}
