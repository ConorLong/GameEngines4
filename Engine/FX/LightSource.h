#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include <glm/common.hpp>
class LightSource
{
public:
	LightSource(glm::vec3 lightPos, glm::vec3 lightColour, float amb, float diff, float spec);
	~LightSource();

	glm::vec3 GetPos() const;
	glm::vec3 GetColour() const;
	float GetSpec() const;
	float GetDiff() const;
	float GetAmb() const;

private:
	glm::vec3 pos;
	glm::vec3 colour;
	float ambient;
	float diffuse;
	float specular;
};
#endif
