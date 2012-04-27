#include "Vec3.h"

///////////////////// Initialization Functions ///////////////////

vec3::vec3(){
	x = y = z = 0;
}

vec3::vec3(double nx, double ny, double nz){
	x = nx;
	y = ny;
	z = nz;
}

vec3::vec3(const vec3& v){
	x = v.x;
	y = v.y;
	z = v.z;
}

///////////////////////// Class Functions ///////////////////////

double vec3::length(){
	return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
}

double vec3::squaredLength(){
	return pow(x,2)+pow(y,2)+pow(z,2);
}

vec3 vec3::normalize(){
	double l = length();
	return vec3(x/l, y/l, z/l);
}

/////////////// Overloaded Functions ///////////////////////

vec3 vec3::operator=(const vec3& source){

	x = source.x;
	y = source.y;
	z = source.z;
	return *this;

}

vec3 vec3::operator+(const vec3& rhs){

	vec3 v;
	v.x = x + rhs.x;
	v.y = y + rhs.y;
	v.z = z + rhs.z;
	return v;

}

vec3 vec3::operator-(const vec3& rhs){

	vec3 v;
	v.x = x - rhs.x;
	v.y = y - rhs.y;
	v.z = z - rhs.z;
	return v;

}

double vec3::operator*(const vec3& rhs){
	return ((x*rhs.x) + (y*rhs.y) + (z*rhs.z));
	
}

vec3 vec3::operator*(double scalar){
	return vec3(scalar*x, scalar*y, scalar*z);
}

vec3 vec3::operator/(double scalar){
	return vec3(scalar/x, scalar/y, scalar/z);
}

bool vec3::operator==(const vec3& rhs){
	return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

////////////////// Non Class Functions ////////////////////

double angle(vec3 a, vec3 b){
	return ((a.x*b.x) - (a.y*b.y) - (a.z*b.z))/(a.length()*b.length());
}

vec3 cross(vec3 a, vec3 b){
	double x = (a.y*b.z)-(a.z*b.y);
	double y = (a.z*b.x)-(a.x*b.z);
	double z = (a.x*b.y)-(a.y*b.x);
	return vec3(x,y,z);
}
