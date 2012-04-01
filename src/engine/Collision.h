#include "ext/glm/glm.hpp"
#include <GL/gl.h>


#define PI 3.14159265
#define mradians(i) ((i)*PI/180)
#define mdegrees(i) ((i)*180/PI)

struct triangle{
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
	glm::vec3 norm;
	bool collided;
};

bool checkPointInTriangle(glm::vec3 point, glm::vec3 pa, glm::vec3 pb, glm::vec3 pc);
int checkCollide(glm::vec3 N,glm::vec3 p,glm::vec3 vel, glm::vec3 ta, glm::vec3 tb, glm::vec3 tc, glm::vec3 &result, float &distance);
bool checkPointInTriangle(glm::vec3 point, glm::vec3 pa, glm::vec3 pb,	glm::vec3 pc);
bool getLowestRoot(float a, float b, float c, float maxR, float* root);
float SquaredLength(glm::vec3 v);
float SignedDistance(glm::vec3 N, glm::vec3 p, glm::vec3 O);
glm::vec3 normal(glm::vec3 a, glm::vec3 b, glm::vec3 c);
GLint circle();
