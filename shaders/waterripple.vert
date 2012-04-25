uniform float time;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex + (sin(time)*100.0);
	gl_FrontColor = gl_Color;
}
