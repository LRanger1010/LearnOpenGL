#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aNormal;
out vec3 v_normal;
out vec3 v_worldPos;
uniform mat4 u_Model;
uniform mat4 u_MVP;
void main()
{
	gl_Position = u_MVP * position;
	v_worldPos = vec3(u_Model * position);
	v_normal = aNormal;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec3 v_normal;
in vec3 v_worldPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform bool isBlinn;

struct Light
{
	vec3 pos;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

void main()
{
	vec3 ambient = light.ambient * material.ambient;

	vec3 lightDir = normalize(light.pos - v_worldPos);
	vec3 norm = normalize(v_normal);
	float diff = max(dot(lightDir, norm), 0);
	vec3 diffuse = diff * light.diffuse * material.diffuse;

	vec3 viewDir = normalize(viewPos - v_worldPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = 0;
	if (isBlinn)
	{
		spec = pow(max(dot(halfDir, norm), 0), material.shininess);
	}
	else
	{
		spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess / 4);
	}
	vec3 specular = spec * light.specular * material.specular;

	vec3 fragColor = ambient + diffuse + specular;
	color = vec4(fragColor, 1.0);
};