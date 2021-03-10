#version 450 core
in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 Position;
in vec3 FragPos;

uniform sampler2D inputTexture;
uniform vec3 viewPos;

out vec4 fColour;
struct Light
{
vec3 colour;
vec3 lightPos;
float ambient;
float diffuse;
float specular;
};
uniform Light light;

void main()
{
	vec3 ambi = light.ambient * texture(inputTexture, TexCoords).rgb * light.colour;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - Position);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * light.diffuse) * texture(inputTexture, TexCoords).rgb * light.colour;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = (spec * light.specular) * light.colour;
	
	vec3 result = ambi + diffuse + specular;
	fColour = vec4(result, 1.0f);
}