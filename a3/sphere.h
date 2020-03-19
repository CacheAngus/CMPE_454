/* sphere.h
 */


#ifndef SPHERE_H
#define SPHERE_H


#include "object.h"
#include "sphere.h"
#include "material.h"


class Sphere : public Object {

  vec3   centre;
  float  radius;
  GLuint VAO;
  int    numQuads;

 public:

  Sphere() {
    VAO = 0;
  }

  Sphere( vec3 c, float r ) {
    centre = c;
    radius = r;
    mat = new Material();
    mat->setDefault();
    mat->kd = vec3( 215/255.0, 181/255.0, 71/255.0 );
    VAO = 0;
  }

  bool rayInt( vec3 rayStart, vec3 rayDir, int objPartIndex, float maxParam,
	       vec3 &intPoint, vec3 &intNorm, vec3 &intTexCoords, float &intParam, Material * & mat, int &intPartIndex );

  void input( istream &stream );
  void output( ostream &stream ) const;
  vec3 polarToCart( float phi, float theta );
  vec3 textureColour( vec3 &p, int objPartIndex, float &alpha, vec3 &texCoords );

  void renderGL( GPUProgram *prog, mat4 &WCS_to_VCS, mat4 &VCS_to_CCS, float scale );

  void renderGL( GPUProgram *prog, mat4 &WCS_to_VCS, mat4 &VCS_to_CCS ) {
    renderGL( prog, WCS_to_VCS, VCS_to_CCS, 1 );
  }
};

#endif
