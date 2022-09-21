#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
out vec3 v_normal;
out vec3 v_worldPos;
out vec2 v_texCoords;
uniform mat4 u_Model;
uniform mat4 u_NormalMatrix;
uniform mat4 u_View;
uniform mat4 u_Proj;
void main()
{
	gl_Position = u_Proj * u_View * u_Model * position;
	v_worldPos = vec3(u_Model * position);
	v_normal = mat3(u_NormalMatrix) * aNormal;
	v_texCoords = aTexCoords;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec3 v_normal;
in vec3 v_worldPos;
in vec2 v_texCoords;
uniform vec3 u_ViewPos;

struct DirLight
{
	vec3 dir;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dirLight;

struct PointLight
{
	vec3 pos;
	float constant;
	float linear;
	float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define pointLightCount 2
uniform PointLight pointLights[pointLightCount];

struct Material
{
	sampler2D diffuse0;
	sampler2D normal0;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

vec3 calcDirLightCol(DirLight light, vec3 norm, vec3 viewDir);
vec3 calcPointLightCol(PointLight light, vec3 norm, vec3 worldPos, vec3 viewDir);

void main()
{
	//vec3 norm = normalize(v_normal);
	vec3 norm = normalize(vec3(texture(material.normal0, v_texCoords)) * 2.0 - 1.0);
	vec3 viewDir = normalize(u_ViewPos - v_worldPos);
	vec3 fragColor = calcDirLightCol(dirLight, norm, viewDir);
	for (int i = 0; i < pointLightCount; i++)
	{
		fragColor += calcPointLightCol(pointLights[i], norm, v_worldPos, viewDir);
	}

	color = vec4(fragColor, 1.0);
};

vec3 calcDirLightCol(DirLight light, vec3 norm, vec3 viewDir)
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse0, v_texCoords));
	vec3 lightDir = normalize(-light.dir);
	float diff = max(dot(lightDir, norm), 0);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse0, v_texCoords));

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0), 32.0);
	vec3 specular = spec * light.specular;

	vec3 fragColor = ambient + diffuse + specular;
	return fragColor;
}

vec3 calcPointLightCol(PointLight light, vec3 norm, vec3 worldPos, vec3 viewDir)
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse0, v_texCoords));
	vec3 lightDir = normalize(light.pos - worldPos);
	float diff = max(dot(lightDir, norm), 0);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse0, v_texCoords));

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0), 32.0);
	vec3 specular = spec * light.specular;

	float distance = length(light.pos - worldPos);
	float atten = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	ambient *= atten;
	diffuse *= atten;
	specular *= atten;

	vec3 fragColor = ambient + diffuse + specular;
	return fragColor;
}