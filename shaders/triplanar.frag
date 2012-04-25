uniform sampler2D tex;
uniform sampler2D tex2;
varying vec2 xy;
varying vec2 xz;
varying vec2 yz;
varying vec3 n;

void main(){
	float intensity = max(dot(vec3(0, 1, -2), normalize(n)) * 1.7, 0.5);
	vec3 blend_weights = abs(n.xyz);
	blend_weights = (blend_weights - vec3(.2)) * 7.0;
	blend_weights = max(blend_weights, 0);
	blend_weights /= (blend_weights.x + blend_weights.y + blend_weights.z).xxx;
	vec4 blended_color;

	vec2 xfacing = yz;
	vec2 yfacing = xz;
	vec2 zfacing = xy;

	vec4 t1 = texture2D(tex, xfacing);
	vec4 t2 = texture2D(tex2, yfacing);
	vec4 t3 = texture2D(tex, zfacing);
	
	blended_color = t1 * vec4(blend_weights.xxx,1) +
					t2 * vec4(blend_weights.yyy,1) +
					t3 * vec4(blend_weights.zzz,1);
					
	gl_FragColor = vec4(normalize(blended_color)*intensity);
	
}
