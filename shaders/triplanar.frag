uniform sampler2D tex;
uniform sampler2D tex2;
uniform sampler2D tex3;
varying vec2 xy;
varying vec2 xz;
varying vec2 yz;
varying vec3 v;
varying vec3 n;

void main(){
	float intensity = max(dot(vec3(0.0, 1.0, -2.0), normalize(n)) * 1.7, 0.5);
	vec3 blend_weights = abs(n.xyz);
	blend_weights = (blend_weights - vec3(.2)) * 10.0;
	blend_weights = max(blend_weights, 0.0);
	blend_weights /= vec3(blend_weights.x + blend_weights.y + blend_weights.z);
	vec4 blended_color;

	vec2 xfacing = yz;
	vec2 yfacing = xz;
	vec2 zfacing = xy;

	vec4 t1 = texture2D(tex, xfacing * 5.0);
	vec4 t2;
	if (n.y < 0) t2 = texture2D(tex3, yfacing * 2.0);
	else t2 = texture2D(tex2, yfacing * 10.0);
	vec4 t3 = texture2D(tex, zfacing * 5.0);
	
	blended_color = t1 * vec4(blend_weights.xxx,1.0) +
					t2 * vec4(blend_weights.yyy,1.0) +
					t3 * vec4(blend_weights.zzz,1.0);
	
	gl_FragColor = vec4(normalize(blended_color)*intensity);
	
}
