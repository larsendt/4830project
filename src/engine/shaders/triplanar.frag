uniform sampler2D tex;
uniform sampler2D tex2;
varying vec2 xy;
varying vec2 xz;
varying vec2 yz;
varying vec3 n;

void main(){

	//float intensity = max(dot(lightDir,normalize(normal)),0.05);
	vec3 blend_weights = abs(n.xyz);
	blend_weights = (blend_weights - vec3(.2)) * 7.0;
	blend_weights = max(blend_weights, vec3(0,0,0));
	blend_weights /= (blend_weights.x + blend_weights.y + blend_weights.z);
	vec4 blended_color;

	vec2 xfacing = yz*2;
	vec2 yfacing = xz*2;
	vec2 zfacing = xy*2;

	vec4 t1 = texture2D(tex2, xfacing);
	vec4 t2 = texture2D(tex, yfacing);
	vec4 t3 = texture2D(tex2, zfacing);
	
	blended_color = t1 * vec4(blend_weights.xxx,1) +
					t2 * vec4(blend_weights.yyy,1) +
					t3 * vec4(blend_weights.zzz,1);
					
	gl_FragColor = vec4(blended_color/*intensity*/);
	
}
