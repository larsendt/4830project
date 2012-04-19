//#version 120

attribute vec3 vertex;
attribute vec3 normal;
attribute vec2 tex;
attribute float rigidity;
varying vec2 coords;
varying vec3 n;
uniform vec3 wind;

void main(void) {
	coords = tex;
	n = normal;
	float time = 0.0;
	vec3 pos = vertex + (1-rigidity)*sin(time)*wind; 
	gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);
}
