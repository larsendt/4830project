

out float V;
out float LightIntensity;

void main()
{
	vec3 pos = vec3(gl_ModelViewMatrix* gl_Vertex);
	vec3 tnorm = normalize(gl_NormalMatrix*gl_Normal);
	vec3 lightVec = normalize(vec3(gl_LightSource[0].position));
	
	LightIntensity = max(dot(lightVec, tnorm), 0.0);
	V = gl_Normal.y;//gl_MultiTexCoord0.s;
	gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
}
