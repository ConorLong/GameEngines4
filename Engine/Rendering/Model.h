#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
class Model
{
public:
	Model(GLuint shader);
	~Model();

	void Render();
	void AddMesh(Mesh* mesh);

private:
	std::vector<Mesh*> meshes;
	GLuint shaderProgram;
};
#endif
