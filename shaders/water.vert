attribute vec3 vertex;

void main(){

	gl_Position = gl_ModelViewProjectionMatrix * vec4(vertex,1.0);

}
