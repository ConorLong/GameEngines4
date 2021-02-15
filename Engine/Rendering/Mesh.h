#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoords;
	glm::vec3 colour;
};

class Mesh
{
public: 
	Mesh(std::vector<Vertex>& vertexList);
	~Mesh();

	void Render();

private:
	void GenerateBuffers();
	GLuint vao, vbo;
	std::vector<Vertex> vertexList;
};
#endif
