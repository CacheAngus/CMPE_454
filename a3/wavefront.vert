// phong vertex shader with textures

#version 300 es

uniform mat4 MVP;		// OCS-to-CCS
uniform mat4 MV;		// OCS-to-VCS

layout (location = 0) in vec3 vertPosition;
layout (location = 1) in vec3 vertNormal;
layout (location = 2) in vec3 vertTexCoords; // just another vertex attribute

smooth out mediump vec3 position;
smooth out mediump vec3 normal;
smooth out mediump vec3 texCoords;
smooth out mediump float depth;

void main()

{
  // calc vertex position in CCS

  gl_Position = MVP * vec4( vertPosition, 1.0 );

  // vertex position in VCS

  position = (MV * vec4( vertPosition, 1.0 )).xyz;

  // calc normal in VCS
  //
  // To do this, apply the non-translational parts of MV to the model
  // normal.  The 0.0 as the fourth component of the normal ensures
  // that no translational component is added.

  normal = vec3( MV * vec4( vertNormal, 0.0 ) );

  // Texture coordinates

  texCoords = vertTexCoords;

  // Depth

  vec4 ccs = MVP * vec4( vertPosition, 1.0 );
  depth = ((ccs.z / ccs.w) + 1.0) * 0.5;
}
