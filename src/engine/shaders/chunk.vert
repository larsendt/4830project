//#version 120

attribute vec3 vertex;
attribute vec3 normal;
attribute vec2 tex_xy;
attribute vec2 tex_xz;
attribute vec2 tex_yz;

varying vec2 xz;

void main(void) {
	xz = tex_xz;
	gl_Position = gl_ModelViewProjectionMatrix * vec4(vertex, 1.0);
}
