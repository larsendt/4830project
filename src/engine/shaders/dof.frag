uniform sampler2D fbo_texture;
uniform sampler2D fbo_depth_tex;
uniform float dX;
uniform float dY;
uniform float time;

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
   float ablur = snoise(vec3(f_texcoord.s, f_texcoord.t*(-time)*.05, time*.02));
   ablur = ablur*.001;
   
   vec4 blur = one*sample(-dX+ablur,+dY+ablur) + two*sample(0.0+ablur,+dY+ablur) + one*sample(+dX+ablur,+dY+ablur)
                + two*sample(-dX+ablur,0.0+ablur) + one*sample(0.0+ablur,0.0+ablur) + two*sample(+dX+ablur,0.0+ablur)
                + one*sample(-dX+ablur,-dY+ablur) + two*sample(0.0+ablur,-dY+ablur) + one*sample(+dX+ablur,-dY+ablur);
    //blur = vec4(1.0,0.0,0.0,1.0);
    blur = blur;
    
	vec4 color = texture2D(fbo_texture,f_texcoord);
	float depth = (texture2D(fbo_depth_tex,f_texcoord).r);
	depth = depth;
	if (depth > .95) depth = (20*(depth-.95));
	else depth = 0;
	gl_FragColor = mix(blur, color, 1-depth);
}
