// Sobel edge detection
//    -1 -2 -1       1 0 -1
// H = 0  0  0   V = 2 0 -2
//     1  2  1       1 0 -1
//
// result = sqrt(H^2 + V^2)

uniform sampler2D fbo_texture;
uniform sampler2D fbo_depth_tex;
uniform float dX;
uniform float dY;
varying vec2 f_texcoord;

vec4 sample(float dx,float dy)
{
	return mix(texture2D(fbo_texture,f_texcoord+vec2(dx,dy)), texture2D(fbo_depth_tex, f_texcoord+vec2(dx,dy)), .99);
   
	//return texture2D(fbo_depth_tex,f_texcoord+vec2(dx,dy));
}

void main()
{
   vec4 H = -sample(-dX,+dY) - 2.0*sample(0.0,+dY) - sample(+dX,+dY)
            +sample(-dX,-dY) + 2.0*sample(0.0,-dY) + sample(+dX,-dY);

   vec4 V =     sample(-dX,+dY)  -     sample(+dX,+dY)
          + 2.0*sample(-dX,0.0)  - 2.0*sample(+dX,0.0)
          +     sample(-dX,-dY)  -     sample(+dX,-dY);

   gl_FragColor = sqrt(H*H+V*V);
}
