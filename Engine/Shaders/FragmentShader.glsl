#version 450 core
in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 Position;
in vec3 FragPos;

uniform sampler2D inputTexture;
uniform vec3 viewPos;
uniform int globalLights;

out vec4 fColour;

struct DirLight
{
vec3 colour;
vec3 lightPos;
float ambient;
float diffuse;
float specular;
float shine;
};

uniform DirLight light[3];

vec3 CalculateDirectLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 ambi = light.ambient * texture(inputTexture, TexCoords).rgb * light.colour;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * light.diffuse) * texture(inputTexture, TexCoords).rgb * light.colour;

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = (spec * light.specular) * light.colour;
	
	return(ambi + diffuse + specular);
}

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result;

	for(int i = 0; i < globalLights; i++){
	result += CalculateDirectLight(light[i], norm, viewDir);
	}

	fColour = vec4(result, 1.0f);
}