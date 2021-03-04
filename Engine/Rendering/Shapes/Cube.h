#ifndef CUBE_H
#define CUBE_H
#include <glm/common.hpp>
#include <vector>

#include "../Mesh.h"


class Cube
{
private:
	std::vector<Vertex> faces;

public:
	Cube(float scale);
	~Cube();
	std::vector<Vertex> GetFaces();
};

#endif