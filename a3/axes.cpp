// axes.cpp


#include "headers.h"
#include "axes.h"


Axes::Axes()

{
  // VAO

  glGenVertexArrays( 1, &VAO );
  glBindVertexArray( VAO );

  // Positions

  vec3 verts[] = {
    vec3(0,0,0), vec3(1,0,0),
    vec3(0,0,0), vec3(0,1,0),
    vec3(0,0,0), vec3(0,0,1)
  };

  GLuint vertexbuffer;
  glGenBuffers( 1, &vertexbuffer );
  glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );
  glBufferData( GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), verts, GL_STATIC_DRAW );
  glEnableVertexAttribArray( 0 );
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

  // Colours

  vec3 colours[] = {
    vec3(1,0,0), vec3(1,0,0),
    vec3(0,1,0), vec3(0,1,0),
    vec3(0.3,0.3,1), vec3(0.3,0.3,1)
  };

  GLuint colourbuffer;
  glGenBuffers( 1, &colourbuffer );
  glBindBuffer( GL_ARRAY_BUFFER, colourbuffer );
  glBufferData( GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), colours, GL_STATIC_DRAW );
  glEnableVertexAttribArray( 1 );
  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );

  // shaders

  program.init( vertShader, fragShader );
}


char *Axes::vertShader = "\n\
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


char *Axes::fragShader = "\n\
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



void Axes::draw( mat4 &MVP_transform )

{
  program.activate();

  glUniformMatrix4fv( glGetUniformLocation( program.id(), "MVP"), 1, GL_TRUE, &MVP_transform[0][0] );

  glLineWidth( 3 );

  glBindVertexArray( VAO );
  glDrawArrays( GL_LINES, 0, 6 );

  glLineWidth( 1 );

  program.deactivate();
}

