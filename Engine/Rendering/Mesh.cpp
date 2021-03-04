#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertList, GLuint textureID, GLuint shaderProgram) : vao(0), vbo(0), ebo(0), vertexList(std::vector<Vertex>()), shaderProgram(0), modelLoc(0), viewLoc(0), projectionLoc(0),textureLoc(0), options(RenderOptions::DEFAULT)
{
	vertexList = vertList;
	this->shaderProgram = shaderProgram;
	this->textureID = textureID;
	GenerateBuffers();
}

Mesh::Mesh(std::vector<Vertex> vertList, GLuint textureID, GLuint shaderProgram) : vao(0), vbo(0), ebo(0), vertexList(std::vector<Vertex>()), shaderProgram(0), modelLoc(0), viewLoc(0), projectionLoc(0), textureLoc(0), options(RenderOptions::DEFAULT)
{
	vertexList = vertList;
	this->shaderProgram = shaderProgram;
	this->textureID = textureID;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	vertexList.clear();
}

void Mesh::Render(Camera* camera, glm::mat4 transform)
{
	switch (options)
	{

	default:
		glUniform1i(textureLoc, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetView()));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->GetPerspective()));

		glBindVertexArray(vao);

		glEnable(GL_DEPTH_TEST);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glDrawArrays(GL_TRIANGLES, 0, vertexList.size());

		glBindVertexArray(0);


	case RenderOptions::DEFAULT :

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->GetPerspective()));
	
	glBindVertexArray(vao);
	
	glEnable(GL_DEPTH_TEST);
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
	
	glDrawArrays(GL_TRIANGLES, 0, vertexList.size());
	
	glBindVertexArray(0);

	case RenderOptions::TEXTURE :

		glUniform1i(textureLoc, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetView()));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->GetPerspective()));

		glBindVertexArray(vao);

		glEnable(GL_DEPTH_TEST);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glDrawArrays(GL_TRIANGLES, 0, vertexList.size());

		glBindVertexArray(0);
	}
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



void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex), &vertexList[0], GL_STATIC_DRAW);

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
}

void Mesh::GenerateBuffers(std::vector<GLuint>& indices)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex), &vertexList[0], GL_STATIC_DRAW);

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

void Mesh::CheckRenderOptions()
{

}

