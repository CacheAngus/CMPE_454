// glverts.h


#ifndef GLVERTS_H
#define GLVERTS_H

#include "headers.h"
#include "seq.h"
#include "gpuProgram.h"

class GLVerts {

  GLuint VAO;
  GPUProgram program;
  static char *vertShader;
  static char *fragShader;

 public:

  GLVerts() {
    program.init( vertShader, fragShader );
  }

  void draw( seq<vec3> &pts, vec3 colour, GLenum renderMode, mat4 &VP );
};

#endif
