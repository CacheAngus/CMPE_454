// GPUProgram class

#ifndef GPU_PROGRAM_H
#define GPU_PROGRAM_H


#include "headers.h"
#include "linalg.h"
#include "seq.h"


class GPUProgram {

  unsigned int program_id;
  unsigned int shader_vp;
  unsigned int shader_fp;

  static seq<unsigned int> active_programs; // stack of active GPU programs to allow nested activation

 public:

  GPUProgram() {};

  GPUProgram( const char *vsFile, const char *fsFile ) {
    initFromFile( vsFile, fsFile );
  }

  void initFromFile( const char *vsFile, const char *fsFile ) {
    
    char* vsText = textFileRead(vsFile);	
    
    if (vsText == NULL) {
      std::cerr << "Vertex shader file '" << vsFile << "' not found." << std::endl;
      return;
    }
    
    char* fsText = textFileRead(fsFile);
    
    if (fsText == NULL) {
      std::cerr << "Fragment shader file '" << fsFile << "' not found." << std::endl;
      return;
    }
    
    init( vsText, fsText );
  }

  ~GPUProgram() {
    glDetachShader( program_id, shader_vp );
    glDeleteShader( shader_vp );

    glDetachShader( program_id, shader_fp );
    glDeleteShader( shader_fp );

    glDeleteProgram( program_id );
  }

  void init( char *vsText, char *fsText );

  int id() {
    return program_id;
  }

  void activate() {
    glUseProgram( program_id );
    active_programs.add( program_id );
  }

  void deactivate() {
    active_programs.remove();
    if (active_programs.size() > 0)
      glUseProgram( active_programs[ active_programs.size()-1 ] ); // re-activate the GPU program that was in use before this one
    else
      glUseProgram( 0 );
  }

  void setMat4( char *name, mat4 &M ) {
    glUniformMatrix4fv( glGetUniformLocation( program_id, name ), 1, GL_TRUE, &M[0][0] );
  }

  void setVec3( char *name, vec3 v ) {
    glUniform3fv( glGetUniformLocation( program_id, name ), 1, &v[0] );
  }

  void setVec3( char *name, vec3 *vs, int size ) {
    glUniform3fv( glGetUniformLocation( program_id, name ), size, &vs[0][0] ); /* indexed array */
  }

  void setVec2( char *name, vec2 v ) {
    glUniform2fv( glGetUniformLocation( program_id, name ), 1, &v[0] );
  }

  void setVec4( char *name, vec4 v ) {
    glUniform4fv( glGetUniformLocation( program_id, name ), 1, &v[0] );
  }

  void setFloat( char *name, float f ) {
    glUniform1f( glGetUniformLocation( program_id, name ), f );
  }

  void setInt( char *name, int i ) {
    glUniform1i( glGetUniformLocation( program_id, name ), i );
  }

  char* textFileRead(const char *fileName);
};

#endif
