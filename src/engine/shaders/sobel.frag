// Blur (low-pass)
//   1 2 1
//   2 1 2   / 13
//   1 2 1

uniform sampler2D fbo_texture;
uniform sampler2D fbo_depth_tex;
uniform float dX;
uniform float dY;
varying vec2 f_texcoord;

vec4 sample(float dx,float dy)
{
	//return texture2D(fbo_depth_tex, f_texcoord+vec2(dx,dy));
   
	return texture2D(fbo_texture,f_texcoord+vec2(dx*2,dy*2));
}

void main()
{
   float one = 1.0/13.0;
   float two = 2.0/13.0;
   vec4 blur = one*sample(-dX,+dY) + two*sample(0.0,+dY) + one*sample(+dX,+dY)
                + two*sample(-dX,0.0) + one*sample(0.0,0.0) + two*sample(+dX,0.0)
                + one*sample(-dX,-dY) + two*sample(0.0,-dY) + one*sample(+dX,-dY);
    //blur = vec4(1.0,0.0,0.0,1.0);
    blur = blur;
	vec4 color = texture2D(fbo_texture,f_texcoord);
	float depth = (texture2D(fbo_depth_tex,f_texcoord).r);
	depth = depth;
	if (depth > .99) depth = (100*(depth-.99));
	else depth = 0;
	gl_FragColor = mix(blur, color, 1-depth);
}
