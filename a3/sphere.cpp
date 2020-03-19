/* sphere.C
 */


#include "headers.h"

#include <math.h>
#include "sphere.h"
#include "main.h"
#include "texture.h"


// Ray / sphere intersection

bool Sphere::rayInt( vec3 rayStart, vec3 rayDir, int objPartIndex, float maxParam,
                     vec3 &intPoint, vec3 &intNorm, vec3 &intTexCoords, float &intParam, Material * &mat, int &intPartIndex )

{
  float a,b,c,d,t0,t1;

  // Does it intersect? ... Solve a quadratic for
  // the parameter at the point of intersection

  a = rayDir * rayDir;
  b = 2 * (rayDir * (rayStart - centre));
  c = (rayStart - centre) * (rayStart - centre) - radius * radius;

  d = b*b - 4*a*c;

  if (d < 0)
    return false;

  // Find the parameter at the point of intersection

  d = sqrt(d);
  t0 = (-b + d) / (2*a);
  t1 = (-b - d) / (2*a);

  intParam = (t0 < t1 ? t0 : t1);

  if (intParam > maxParam)
    return false; // too far away

  // Compute the point of intersection

  intPoint = rayStart + intParam * rayDir;

  // Compute the normal at the intersection point

  intNorm = (intPoint - centre).normalize();

  mat = this->mat;

  return true;
}


// Output a sphere

void Sphere::output( ostream &stream ) const

{
  stream << "sphere" << endl
         << "  " << radius << endl
         << "  " << centre << endl;
}


// Input a sphere

void Sphere::input( istream &stream )

{
  skipComments( stream );  stream >> radius;
  skipComments( stream );  stream >> centre;
}


// Render with openGL

#define PI          3.1415926
#define PHI_STEP    PI/8.0
#define THETA_STEP  PI/8.0

void Sphere::renderGL( GPUProgram *prog, mat4 &WCS_to_VCS, mat4 &VCS_to_CCS, float s )

{
  if (VAO == 0) { // create VBO

    // Count the quads
    //
    // Do it this way to avoid discrepences with roundoff

    numQuads = 0;
    for (float phi=0; phi<1.99*PI; phi+=PHI_STEP)
      for (float theta=-0.5*PI; theta<0.49*PI; theta+=THETA_STEP)
        numQuads++;

    vec3 *attribs = new vec3[3*3*numQuads*2]; // 3 vertices x 3 attributes x (numQuads*2) triangles

    vec3 *pos  = &attribs[0];
    vec3 *norm = &attribs[3*numQuads*2];
    vec3 *tex  = &attribs[2*3*numQuads*2];

    for (float phi=0; phi<1.99*PI; phi+=PHI_STEP)
      for (float theta=-0.5*PI; theta<0.49*PI; theta+=THETA_STEP) {

        // One quad on the sphere

        // normals

        vec3 Nll = polarToCart( phi,          theta );
        vec3 Nlr = polarToCart( phi+PHI_STEP, theta );
        vec3 Nur = polarToCart( phi+PHI_STEP, theta+THETA_STEP );
        vec3 Nul = polarToCart( phi,          theta+THETA_STEP );

        // positions

        vec3 ll = centre + radius * Nll;
        vec3 lr = centre + radius * Nlr;
        vec3 ur = centre + radius * Nur;
        vec3 ul = centre + radius * Nul;

        // texture coords

        vec3 Tll( phi / (2*PI),            theta / PI + 0.5,              0 );
        vec3 Tlr( (phi+PHI_STEP) / (2*PI), theta / PI + 0.5,              0 );
        vec3 Tur( (phi+PHI_STEP) / (2*PI), (theta+THETA_STEP) / PI + 0.5, 0 );
        vec3 Tul( phi / (2*PI),            (theta+THETA_STEP) / PI + 0.5, 0 );

        // First triangle

        *(pos++) = ll;
        *(pos++) = lr;
        *(pos++) = ur;

        *(norm++) = Nll;
        *(norm++) = Nlr;
        *(norm++) = Nur;

        *(tex++) = Tll;
        *(tex++) = Tlr;
        *(tex++) = Tur;

        // Second triangle

        *(pos++) = ll;
        *(pos++) = ur;
        *(pos++) = ul;

        *(norm++) = Nll;
        *(norm++) = Nur;
        *(norm++) = Nul;

        *(tex++) = Tll;
        *(tex++) = Tur;
        *(tex++) = Tul;
      }

    glGenVertexArrays( 1, &VAO );
    glBindVertexArray( VAO );

    GLuint VBO;
    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vec3)*3*3*numQuads*2, attribs, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 0 );
    
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(vec3)*3*numQuads*2) );
    glEnableVertexAttribArray( 1 );

    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(vec3)*2*3*numQuads*2) );
    glEnableVertexAttribArray( 2 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );

    delete[] attribs;
  }

  // Draw

  mat->setMaterialForOpenGL( prog );

  mat4 MV  = WCS_to_VCS * translate( centre ) * scale( s, s, s ) * translate( -1 * centre ); // scale by s first
  mat4 MVP = VCS_to_CCS * MV;

  gpuProg->setMat4( "MV",  MV );
  gpuProg->setMat4( "MVP", MVP );

  glBindVertexArray( VAO );
  glDrawArrays( GL_TRIANGLES, 0, 3*numQuads*2 );
  glBindVertexArray( 0 );
}


vec3 Sphere::polarToCart( float phi, float theta )

{
  return vec3( cos(phi)*cos(theta), sin(phi)*cos(theta), sin(theta) );
}


vec3 Sphere::textureColour( vec3 &p, int objPartIndex, float &alpha, vec3 &texCoords )

{
  // No texture map?

  if (mat->texture == NULL) {
    alpha = 1;
    return vec3(1,1,1);
  }

  // Texture map:

  vec3 dir = (p - centre).normalize();

  float theta = asin(dir.z) / PI + 0.5;
  float phi = atan2( dir.y, dir.x ) / (2*PI);
  if (phi < 0) phi++;

  return mat->texture->texel( phi, theta, alpha );
}
