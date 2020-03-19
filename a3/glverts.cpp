// glverts.cpp



#include "glverts.h"
#include "gpuProgram.h"


void GLVerts::draw( seq<vec3> &pts, vec3 colour, GLenum renderMode, mat4 &MVP  )

{
  if (pts.size() == 0)
    return;

  // VAO

  GLuint VAO;
  
  glGenVertexArrays( 1, &VAO );
  glBindVertexArray( VAO );

  // Positions

  GLuint vertexbuffer;
  glGenBuffers( 1, &vertexbuffer );
  glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );
  glBufferData( GL_ARRAY_BUFFER, 3 * sizeof(GLfloat) * pts.size(), &pts[0], GL_STATIC_DRAW );
  glEnableVertexAttribArray( 0 );
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

  // Colours

  vec3 *colours = new vec3[ pts.size() ];
  for (int i=0; i<pts.size(); i++)
    colours[i] = colour;

  GLuint colourbuffer;
  glGenBuffers( 1, &colourbuffer );
  glBindBuffer( GL_ARRAY_BUFFER, colourbuffer );
  glBufferData( GL_ARRAY_BUFFER, 3 * sizeof(GLfloat) * pts.size(), colours, GL_STATIC_DRAW );
  glEnableVertexAttribArray( 1 );
  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );

  // Draw

  program.activate();

  glUniformMatrix4fv( glGetUniformLocation( program.id(), "MVP"), 1, GL_TRUE, &MVP[0][0] );

  glBindVertexArray( VAO );
  glDrawArrays( renderMode, 0, pts.size() );

  program.deactivate();

  glDeleteBuffers( 1, &vertexbuffer );
  glDeleteBuffers( 1, &colourbuffer );

  glDeleteVertexArrays( 1, &VAO );

  delete[] colours;
}



char *GLVerts::vertShader = "\n\
\n\
  #version 300 es\n\
\n\
  uniform mat4 MVP;\n\
\n\
  layout (location = 0) in mediump vec3 vertPosition;\n\
  layout (location = 1) in mediump vec3 vertColour;\n\
\n\
  smooth out mediump vec3 colour;\n\
\n\
  void main() {\n\
    gl_Position = MVP * vec4( vertPosition, 1.0f );\n\
    colour = vertColour;\n\
  }\n\
";


 char *GLVerts::fragShader = "\n\
\n\
  #version 300 es\n\
\n\
  smooth in mediump vec3 colour;\n\
  out mediump vec4 outputColour;\n\
\n\
  void main() {\n\
    outputColour = vec4( colour, 1.0 );\n\
  }\n\
";



