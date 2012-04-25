//#version 120

attribute vec3 vertex;
attribute vec3 normal;
attribute vec2 tex_xy;
attribute vec2 tex_xz;
attribute vec2 tex_yz;
varying vec2 xy;
varying vec2 xz;
varying vec2 yz;
varying vec3 n;

void main(void) {
	xy = tex_xy;
	xz = tex_xz;
	yz = tex_yz;
	n = normal;
	vec3 vert = vertex;
	vert.y *= -1;
	gl_Position = gl_ModelViewProjectionMatrix * vec4(vert, 1.0);
}
