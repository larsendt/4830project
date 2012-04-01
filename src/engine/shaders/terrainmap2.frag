varying float h;
varying vec3 normal,lightDir;
uniform sampler2D rock;
uniform sampler2D grass;
uniform sampler2D sand;
//uniform sampler2D glass;
uniform sampler2D map;

void main()
{
	vec4 ct, cf;
	vec4 emission = vec4(0,0,0,0);
	float intensity = max(dot(lightDir,normalize(normal)),0.05);
	cf = intensity*vec4(1,1,1,1);
	vec4 mapVal = texture2D(map, gl_TexCoord[0].st);
	vec4 color = texture2D(rock, gl_TexCoord[0].st*4);
	vec4 color2 = texture2D(grass, gl_TexCoord[0].st*4);
	vec4 color3 =  texture2D(sand, vec2(gl_TexCoord[0].s*4,gl_TexCoord[0].t*4));
	vec4 height;
	height = mix(color,color2,clamp(abs((h-100)/100.0),0,1));
	ct = mix(height,color,clamp((h-100)/100.0,0,1));
	//if (h<100.0) ct = mix(color,color2,clamp(abs((h-100)/100.0),0,1));
	//else ct = color;
	
	ct = mix(ct, color3,clamp(mapVal.r,0,1));
	//emission = vec4(1,0,0,1)*.5 * (1-intensity);
	
	gl_FragColor = vec4(ct*cf)+vec4(emission);
}


