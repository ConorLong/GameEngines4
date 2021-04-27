#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>
using namespace glm;
class Plane
{
public:
	Plane();
	Plane(const vec3 &P1, const vec3 &P2, const vec3 &P3);
	Plane CreatePlaneFrom3Points(const vec3& P1, const vec3& P2, const vec3& P3);
	float SignedDistance(const vec3& p);

	vec4 p;
	vec3 normal;
};
#endif
