uniform sampler2D fbo_texture;
uniform sampler2D fbo_depth_tex;
uniform float dX;
uniform float dY;
uniform float time;
varying vec2 f_texcoord;

vec4 sample(float dx,float dy)
{
	return texture2D(fbo_depth_tex,f_texcoord+vec2(dx,dy));
}

void main()
{
   float one = 1.0/13.0;
   float two = 2.0/13.0;
   vec4 H = -sample(-dX,+dY) - 2.0*sample(0.0,+dY) - sample(+dX,+dY)
            +sample(-dX,-dY) + 2.0*sample(0.0,-dY) + sample(+dX,-dY);

   vec4 V =     sample(-dX,+dY)  -     sample(+dX,+dY)
          + 2.0*sample(-dX,0.0)  - 2.0*sample(+dX,0.0)
          +     sample(-dX,-dY)  -     sample(+dX,-dY);

    float edgeDepth = sqrt(H*H+V*V).r;
    edgeDepth = sqrt(edgeDepth);
    if (edgeDepth>.08) edgeDepth = 1;
    else edgeDepth = 0;
	vec4 color = texture2D(fbo_texture,f_texcoord);
	
	gl_FragColor =  color - vec4(edgeDepth);
}
