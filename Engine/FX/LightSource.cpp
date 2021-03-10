#include "LightSource.h"

LightSource::LightSource(glm::vec3 lightPos, glm::vec3 lightColour, float amb, float diff, float spec) : pos(glm::vec3()), colour(glm::vec3()), ambient(0.0f), diffuse(0.0f), specular(0.0f)
{
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPos() const
{
	return pos;
}

glm::vec3 LightSource::GetColour() const
{
	return colour;
}

float LightSource::GetSpec() const
{
	return specular;
}

float LightSource::GetDiff() const
{
	return diffuse;
}

float LightSource::GetAmb() const
{
	return ambient;
}
