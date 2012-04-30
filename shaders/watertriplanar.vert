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
uniform float time;

void main(void) {
	xy = tex_xy;
	xz = tex_xz;
	yz = tex_yz;
	n = normal;
	vec3 vert = vertex;
	vert.y *= -1;
	float ratio = abs(vert.y / 128.0);
	vert.x += cos(time + vert.x) * (ratio);
	vert.z += sin(time + vert.z) * (ratio);
	gl_Position = gl_ModelViewProjectionMatrix * vec4(vert, 1.0);
}
