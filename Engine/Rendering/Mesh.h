#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <bitset>

#include "Camera.h"
#include"../Graphics/MaterialHandler.h"

struct Light {
	GLuint  lightPos, ambi, diff, spec, colour, shine;
};

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<unsigned int> meshIndices;
	Material material;
};

//Probably put this in its own header
enum class RenderOptions
{
		DEFAULT = 0,
		TEXTURE = (1 << 0),
		CUBETEXTURE = (1 << 4)

};
inline RenderOptions operator |(RenderOptions a, RenderOptions b)
{
	return static_cast<RenderOptions>(static_cast<int>(a) | static_cast<int>(b));
}
inline RenderOptions& operator |=(RenderOptions& a, RenderOptions b)
{
	return a= a |b;
}

class Mesh
{
	
public: 

	Mesh(SubMesh& sMesh, GLuint shaderProgram);
	Mesh();
	~Mesh();

	float GetShine() const;

	void Render(Camera* camera, std::vector<glm::mat4> instances_);
	void SetRenderOption(enum RenderOptions option);
	void SetRenderOption(std::vector<enum RenderOptions> optionList);
	GLuint GetShaderProgram() const;
private:

	void LinkLightUniforms();
	void GenerateBuffers();
	void GenerateBuffers(std::vector<GLuint>& indices);
	void CheckRenderOptions();

	GLuint shaderProgram;
	SubMesh subMesh;

	GLuint lightsInScene;
	GLuint modelLoc, viewLoc, projectionLoc, textureLoc, viewPos;
	GLuint vao, vbo, ebo;

	RenderOptions options;
	float shine;

	std::vector<Light> lightUniforms;
	
};
#endif
