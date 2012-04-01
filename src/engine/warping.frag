//  Set the fragment color

void main()
{
	vec4 color;
	vec4 blurg = normalize(gl_FragCoord);
	color = vec4(vec3(blurg.xyy),1);
 	gl_FragColor = color;
}
