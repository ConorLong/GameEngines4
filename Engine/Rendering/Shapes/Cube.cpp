#include "Cube.h"

std::vector<Vertex> Cube::GetFaces()
{
	return faces;
}

Cube::Cube(float scale){
	Vertex v;
	faces.reserve(36);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v.colour = glm::vec3(0.583f, 0.771f, 0.014f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v.colour = glm::vec3(0.609f, 0.115f, 0.436f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v.colour = glm::vec3(0.327f, 0.483f, 0.844f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v.colour = glm::vec3(0.822f, 0.569f, 0.201f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v.colour = glm::vec3(0.435f, 0.602f, 0.223f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v.colour = glm::vec3(0.310f, 0.747f, 0.185f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v.colour = glm::vec3(0.597f, 0.770f, 0.761f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v.colour = glm::vec3(0.559f, 0.436f, 0.730f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v.colour = glm::vec3(0.359f, 0.583f, 0.152f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v.colour = glm::vec3(0.483f, 0.596f, 0.789f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v.colour = glm::vec3(0.559f, 0.861f, 0.639f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v.colour = glm::vec3(0.195f, 0.548f, 0.859f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v.colour = glm::vec3(0.014f, 0.184f, 0.576f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v.colour = glm::vec3(0.771f, 0.328f, 0.970f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v.colour = glm::vec3(0.406f, 0.615f, 0.116f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v.colour = glm::vec3(0.676f, 0.977f, 0.133f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v.colour = glm::vec3(0.971f, 0.572f, 0.833f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v.colour = glm::vec3(0.140f, 0.616f, 0.489f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v.colour = glm::vec3(0.997f, 0.513f, 0.064f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v.colour = glm::vec3(0.945f, 0.719f, 0.592f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v.colour = glm::vec3(0.543f, 0.021f, 0.978f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v.colour = glm::vec3(0.279f, 0.317f, 0.505f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v.colour = glm::vec3(0.167f, 0.620f, 0.077f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v.colour = glm::vec3(0.347f, 0.857f, 0.137f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v.colour = glm::vec3(0.055f, 0.953f, 0.042f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v.colour = glm::vec3(0.714f, 0.505f, 0.345f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v.colour = glm::vec3(0.783f, 0.290f, 0.734f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v.colour = glm::vec3(0.722f, 0.645f, 0.174f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v.colour = glm::vec3(0.302f, 0.455f, 0.848f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v.colour = glm::vec3(0.225f, 0.587f, 0.040f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v.colour = glm::vec3(0.517f, 0.713f, 0.338f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 0.0f);
	v.colour = glm::vec3(0.053f, 0.959f, 0.120f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v.colour = glm::vec3(0.393f, 0.621f, 0.362f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(1.0f, 1.0f);
	v.colour = glm::vec3(0.673f, 0.211f, 0.457f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 1.0f);
	v.colour = glm::vec3(0.820f, 0.883f, 0.371f);
	v.position *= scale;
	faces.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.texCoords = glm::vec2(0.0f, 0.0f);
	v.colour = glm::vec3(0.982f, 0.099f, 0.879f);
	v.position *= scale;
	faces.push_back(v);
}

Cube::~Cube()
{
}

