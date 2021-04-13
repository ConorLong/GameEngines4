#version 450 core
in vec3 Normal;
in vec2 TexCoords;
in vec3 Position;
in vec3 FragPos;

uniform vec3 viewPos;
uniform int globalLights;

out vec4 fColour;

struct Material
{
sampler2D diffuseMap;
vec3 ambient;
vec3 diffuse;
vec3 specular;
float shine;
float alpha;
};

struct DirLight
{
vec3 colour;
vec3 lightPos;
float ambient;
float diffuse;
float specular;
};

uniform DirLight light[3];
uniform Material material;

vec3 CalculateDirectLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 ambi = light.ambient * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.colour;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.colour;

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
	vec3 specular = (spec * material.specular) * light.colour;
	
	return(ambi + diffuse + specular);
}

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result;

	for(int i = 0; i < globalLights; i++)
	{
		result += CalculateDirectLight(light[i], norm, viewDir);
	}
	
	fColour = vec4(result, material.alpha);
}