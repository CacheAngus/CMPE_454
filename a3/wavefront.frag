// Phong fragment shader with textures
//
// Phong shading with diffuse and specular components

#version 300 es

uniform sampler2D objTexture;
uniform bool      texturing;        // =1 if object's texture is provided

uniform mediump vec3 lightPos[4];   // array size must match MAX_NUM_LIGHTS (= 4) in scene.cpp
uniform mediump vec3 lightIin[4];   // array size must match MAX_NUM_LIGHTS (= 4) in scene.cpp
uniform int numLights;
uniform bool useHeadlights;

uniform mediump vec3 kd;
uniform mediump vec3 ks;
uniform mediump vec3 ka;
uniform mediump vec3 Ia;
uniform mediump vec3 Ie;
uniform mediump float shininess;

smooth in mediump vec3 position;
smooth in mediump vec3 normal;
smooth in mediump vec3 texCoords;
smooth in mediump float depth;

out mediump vec4 outputColour;

void main()

{
  mediump vec3 N = normalize( normal );

  // Compute the outgoing colour

  mediump vec3 Iout = vec3(0,0,0);

  for (int i=0; i<numLights; i++) { // add contribution from each (positional) light

    mediump vec3 L = normalize( lightPos[i] - position );      

    mediump float NdotL = dot( N, L );

    if (NdotL > 0.0) {

      // diffuse component

      mediump vec3 colour;

      if (texturing)
	colour = texture( objTexture, texCoords.st ).rgb * kd;
      else
	colour = kd;

      Iout += NdotL * (colour * lightIin[i]);

      Iout += (ka * Ia) * colour;

      // specular component

      mediump vec3 R = (2.0 * NdotL) * N - L;
      mediump vec3 V = vec3(0.0,0.0,1.0);	// direction toward eye in the VCS

      mediump float RdotV = dot( R, V );

      if (RdotV > 0.0)
	Iout += pow( RdotV, shininess ) * (ks * lightIin[i]);
    }
  }

  outputColour = vec4( Iout, 1.0 );
}
