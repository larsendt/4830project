//  Cartoon vertex shader
//  Adapted from Lighthouse3D

varying vec4 N;
varying vec4 L;
varying vec3 vpos;
varying float A;
uniform float time;

// found this on stackoverflow

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

//

void main()
{
	//A = sin(time)*rand(vec2(gl_Vertex.x, gl_Vertex.z));
	//  P is the vertex coordinate on body
	vec4 P = vec4(gl_ModelViewMatrix * gl_Vertex);
	//  L is the light vector
	vpos = gl_Vertex.xyz;
	L = vec4(gl_LightSource[0].position) - P;
	//  Normal
	N = vec4(normalize(gl_NormalMatrix * gl_Normal),1);
	//vec4 glcolor = gl_Color;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
} 
