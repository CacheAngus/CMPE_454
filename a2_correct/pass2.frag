// Pass 2 fragment shader
//
// Apply diffuse lighting to fragment.  Later do Phong lighting.
//
// Determine whether fragment is in shadow.  If so, reduce intensity to 50%.

#version 300 es
precision mediump float;


uniform vec3      lightDir;	    // direction to light in WCS
uniform vec3      eyePosition;	    // position of eye in WCS
uniform mat4      WCS_to_lightCCS;  // transform from WCS to light's CCS
uniform sampler2D shadowBuffer;     // texture [0,1]x[0,1] of depth from light.  Values in [0,1].
uniform sampler2D objTexture;       // object's texture (might not be provided)
uniform bool      texturing;        // =1 if object's texture is provided

in vec3 colour;        // fragment colour
in vec3 normal;        // fragment normal in WCS
in vec3 wcsPosition;   // fragemnt position in WCS
in vec2 texCoords;     // fragment texture coordinates (if provided) 

out vec4 fragColour;   // fragment's final colour


void main()

{
  // Calculate the position of this fragment in the light's CCS.

  vec4 ccsLightPos = WCS_to_lightCCS*vec4(wcsPosition, 0.1f); // CHANGE THIS

  // Calculate the depth of this fragment in the light's CCS in the range [0,1]
  
  float fragDepth = 0.5*(ccsLightPos.z/ccsLightPos.w+1.0); // CHANGE THIS

  // Determine the (x,y) coordinates of this fragment in the light's
  // CCS in the range [0,1]x[0,1].
  float fragX = 0.5*(ccsLightPos.x/ccsLightPos.w+1.0); 
  float fragY = 0.5*(ccsLightPos.y/ccsLightPos.w+1.0); 
  vec2 shadowTexCoords = vec2(fragX, fragY); // CHANGE THIS

  // Look up the depth from the light in the shadowBuffer texture.

  float shadowDepth = texture(shadowBuffer, shadowTexCoords).r; // CHANGE THIS

  // Determine whether the fragment is in shadow.
  //
  // If results look bad, add a bit to the shadow texture depth to
  // prevent z-fighting.
  if(shadowDepth < fragDepth){
  fragColour = vec4(shadowDepth, shadowDepth, shadowDepth, 1.0);

	}

  // YOUR CODE HERE
 mediump vec3 Iin = vec3( 1.0, 1.0, 1.0 ); // incoming light
  mediump vec3 Ia  = vec3( 0.1, 0.1, 0.1 ); // ambient light
  mediump vec3 kd  = colour;		    // kd = surface colour from calling program
  mediump vec3 ks  = vec3( 0.4, 0.4, 0.4 ); // ks = specular coefficients
  mediump float shininess = 10.0;	    // shininess = specular exponent

  // Since the normal is interpolated, it might not be unit length.  So normalize it.

  mediump vec3 N = normalize( normal);
  mediump vec3 V = normalize( -1.0 * vec3(ccsLightPos));       // Looking toward the eye at (0,0,0) in the VCS 

  mediump float NdotL = dot( N, lightDir );

  // Compute the outgoing colour

  mediump vec3 Iout = Ia;

  
  if (NdotL > 0.0) {  // light is above the surface

    // diffuse component

       
     mediump vec3 Idif = NdotL * vec3( kd.r * Iin.r, kd.g * Iin.g, kd.b * Iin.b ); 

    // specular component

  
      
      mediump vec3 R = (2.0 * NdotL) * N - lightDir;

      mediump float RdotV = dot( R, V );

      mediump vec3 Ispec = Ia;

      if (RdotV > 0.0)
	Ispec = pow( RdotV, shininess ) * vec3( ks.r * Iin.r, ks.g * Iin.g, ks.b * Iin.b );
      Iout += Idif + Ispec;

  }


  // Compute illumination.  Initially just do diffuse "N dot L".  Later do Phong.
  if(texturing){
  mediump vec4 textColour = vec4(texture(objTexture, texCoords).rgb, 1.0);
  fragColour = textColour;
  }
  else{
   fragColour = vec4(Iout, 1.0f);
  }


  

}
