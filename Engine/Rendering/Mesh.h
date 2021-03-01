#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 colour;
};

class Mesh
{
public: 
	Mesh(std::vector<Vertex>& vertexList, GLuint shaderProgram);
	Mesh(std::vector<Vertex>& vertList, std::vector<GLuint>& indices);
	~Mesh();

	void Render(Camera* camera, glm::mat4 transform);

private:
	void GenerateBuffers();
	void GenerateBuffers(std::vector<GLuint>& indices);
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projectionLoc;
	GLuint vao, vbo, ebo;
	std::vector<Vertex> vertexList;
	
};
#endif
