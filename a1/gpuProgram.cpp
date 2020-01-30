// GPUProgram class


#include "gpuProgram.h"


char* GPUProgram::textFileRead(const char *fileName)

{
  char* text = "";
    
  if (fileName != NULL) {
    
    FILE *file = fopen( fileName, "rt" );

    if (file == NULL) {

      std::cerr << "File " << fileName << " could not be opened" << std::endl;
      text = "";

    } else {

      fseek(file, 0, SEEK_END);
      int count = ftell(file);
      rewind(file);
            
      if (count > 0) {
	text = (char*)malloc(sizeof(char) * (count + 1));
	count = fread(text, sizeof(char), count, file);
	text[count] = '\0';
      }

      fclose(file);
    }
  }
  
  return _strdup(text);
}


static void validateShader(GLuint shader, const char* file = 0)

{
  const unsigned int BUFFER_SIZE = 512;
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  GLsizei length = 0;
    
  glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);

  if (length > 0)
    std::cout << "Shader " << shader << " (" << (file?file:"") << ") compile log: " << std::endl << buffer << std::endl;
}


static void validateProgram(GLuint program)

{
  const unsigned int BUFFER_SIZE = 512;
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  GLsizei length = 0;
    
  memset(buffer, 0, BUFFER_SIZE);

  glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);

  if (length > 0)
    std::cout << "Program " << program << " link log: " << buffer << std::endl;
    
  glValidateProgram(program);

  GLint status;
  glGetProgramiv(program, GL_VALIDATE_STATUS, &status);

  if (status == GL_FALSE) {
    std::cout << "Error validating program " << program << std::endl;
    exit(1);
  }
}


void GPUProgram::init( char *vsText, char *fsText )

{
  glErrorReport( "before GPUProgram::init" );

  // Vertex shader

  shader_vp = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource( shader_vp, 1, (const char**) &vsText, 0 );
  glCompileShader( shader_vp );
  validateShader( shader_vp, "vertex shader" );
    
  // Fragment shader

  shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource( shader_fp, 1, (const char **) &fsText, 0 );
  glCompileShader( shader_fp );
  validateShader( shader_fp, "fragment shader" );
    
  // GLSL program

  program_id = glCreateProgram();
  glAttachShader( program_id, shader_vp );
  glAttachShader( program_id, shader_fp );
  glLinkProgram( program_id );
  validateProgram( program_id );

  glErrorReport( "after GPUProgram::init" );
}


// Draw n vec3 vertices.  Assume a single attribute 0.

void GPUProgram::drawVertices( vec3 *verts, int n, GLenum drawType, vec3 colour )

{
  // Build VBO

  GLuint VBO;
  
  glGenBuffers( 1, &VBO );
  glBindBuffer( GL_ARRAY_BUFFER, VBO );
  glBufferData( GL_ARRAY_BUFFER, n * sizeof(vec3), verts, GL_STREAM_DRAW );

  // Attribute 0

  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
  glEnableVertexAttribArray( 0 );

  // Set colour
  
  glUniform3fv( glGetUniformLocation( id(), "colour" ), 1, &colour[0] );

  // Render it

  glDrawArrays( drawType, 0, n );

  // Done

  glDisableVertexAttribArray( 0 );
  glBindBuffer( GL_ARRAY_BUFFER, 0 );
  glDeleteBuffers( 1, &VBO );
}

