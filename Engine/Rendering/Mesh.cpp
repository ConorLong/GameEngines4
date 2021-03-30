#include "Mesh.h"
#include"../Core/Debug.h"
#include<iostream>
#include<string>
#include "../Core/EngineCore.h"
Mesh::Mesh(SubMesh& sMesh, GLuint shaderProgram) : vao(0), vbo(0), ebo(0), shaderProgram(0), modelLoc(0), viewLoc(0), projectionLoc(0),textureLoc(0), shine(0), options(RenderOptions::DEFAULT)
{
	
	subMesh = sMesh;
	this->shaderProgram = shaderProgram;
	GenerateBuffers();
}

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera, std::vector<glm::mat4> instances_)
{

		glUniform1i(textureLoc, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, subMesh.textureID);

		std::vector<LightSource*> lights = camera->GetLightSources();

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetView()));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->GetPerspective()));
		glUniform3fv(viewPos, 1, glm::value_ptr(camera->GetPosition()));

		glUniform1i(lightsInScene, camera->GetLightSources().size());
		//Update all light uniforms
		for (int i = 0; i < camera->GetLightSources().size(); i++) {
		glUniform3fv(lightUniforms[i].lightPos, 1, glm::value_ptr(lights[i]->GetPos()));
	    glUniform3fv(lightUniforms[i].colour, 1, glm::value_ptr(lights[i]->GetColour()));
		glUniform1f(lightUniforms[i].ambi, lights[i]->GetAmb());
		glUniform1f(lightUniforms[i].diff, lights[i]->GetDiff());
		glUniform1f(lightUniforms[i].spec, lights[i]->GetSpec());
		}

		glUniform1f(shine, GetShine());
		glBindVertexArray(vao);

		glEnable(GL_DEPTH_TEST);

		for (int i = 0; i < instances_.size(); i++ ) {
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
			glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
		}

		glBindVertexArray(0);

	
}

void Mesh::SetRenderOption(enum RenderOptions option)
{ 
	options |= option;
}

void Mesh::SetRenderOption(std::vector<enum RenderOptions> optionList)
{
	for (auto m : optionList) {
		options |= m;
	}
}



void Mesh::LinkLightUniforms()
{
	
	for (GLuint i = 0; i < EngineCore::GetInstance()->GetCamera()->GetLightSources().size(); i++) {
		lightUniforms.emplace_back(Light());
		std::string num = std::to_string(i);
		lightUniforms[i].lightPos = glGetUniformLocation(shaderProgram, ("light["+num+"].lightPos").c_str());
		lightUniforms[i].ambi = glGetUniformLocation(shaderProgram, ("light["+num+"].ambient").c_str());
		lightUniforms[i].diff = glGetUniformLocation(shaderProgram, ("light["+num+"].diffuse").c_str());
		lightUniforms[i].spec = glGetUniformLocation(shaderProgram, ("light["+num+"].specular").c_str());
		lightUniforms[i].colour = glGetUniformLocation(shaderProgram, ("light["+num+"].colour").c_str());
		lightUniforms[i].shine = glGetUniformLocation(shaderProgram, ("light["+num+"].shine").c_str());
	}
		lightsInScene = glGetUniformLocation(shaderProgram, "globalLights");
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	viewPos = glGetUniformLocation(shaderProgram, "viewPos");


	LinkLightUniforms();

	//Nice way to check for active uniforms
	//int total = -1;
	//glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &total);
	//for (int i = 0; i < total; ++i) {
	//	int name_len = -1, num = -1;
	//	GLenum type = GL_ZERO;
	//	char name[100];
	//	glGetActiveUniform(shaderProgram, GLuint(i), sizeof(name) - 1,
	//		&name_len, &num, &type, name);
	//	name[name_len] = 0;
	//	GLuint location = glGetUniformLocation(shaderProgram, name);
	//
	//	printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
	//}

}

void Mesh::GenerateBuffers(std::vector<GLuint>& indices)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);
	 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


float Mesh::GetShine() const
{
	return shine;
}
void Mesh::CheckRenderOptions()
{

}

