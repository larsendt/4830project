#ifndef VECTOR
#define VECTOR
#include <math.h>
class vec3{
	public:
		vec3();
		vec3(double nx, double ny, double nz);
		vec3(const vec3& v);
		
		double length();
		double squaredLength();
		vec3 normalize();
		
		vec3 operator=(const vec3& source);
		vec3 operator+(const vec3& rhs);
		vec3 operator-(const vec3& rhs);
		vec3 operator*(double scalar);
		vec3 operator/(double scalar);
		double operator*(const vec3& rhs);
		bool operator==(const vec3& rhs);
		
		double x;
		double y;
		double z;
		
		
};

double angle(vec3 a, vec3 b);
vec3 cross(vec3 a, vec3 b);

#endif
