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
	Mesh(std::vector<Vertex>& vertList, std::vector<GLuint>& indices);
	~Mesh();

	void Render();

private:
	void GenerateBuffers();
	void GenerateBuffers(std::vector<GLuint>& indices);
	GLuint vao, vbo, ebo;
	std::vector<Vertex> vertexList;
};
#endif
