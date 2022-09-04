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
uniform mat4 u_MVP;
void main()
{
	gl_Position = u_MVP * position;
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
uniform vec3 viewPos;

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

struct SpotLight
{
	vec3 pos;
	vec3 dir;
	float cutOff;
	float outterCutOff;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform SpotLight spotLight;

struct Material
{
	sampler2D diffuse0;
	sampler2D diffuse1;
	sampler2D diffuse2;
	sampler2D diffuse3;
	sampler2D diffuse4;
	sampler2D diffuse5;
	sampler2D specular0;
	sampler2D specular1;
	sampler2D specular2;
	sampler2D specular3;
	sampler2D specular4;
	float shininess;
};
uniform Material material;

vec3 calcDirLightCol(DirLight light, vec3 norm, vec3 viewDir);
vec3 calcPointLightCol(PointLight light, vec3 norm, vec3 worldPos, vec3 viewDir);
vec3 calcSpotLightCol(SpotLight light, vec3 norm, vec3 worldPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(v_normal);
	vec3 viewDir = normalize(viewPos - v_worldPos);
	vec3 fragColor = calcDirLightCol(dirLight, norm, viewDir);
	for (int i = 0; i < pointLightCount; i++)
	{
		fragColor += calcPointLightCol(pointLights[i], norm, v_worldPos, viewDir);
	}
	fragColor += calcSpotLightCol(spotLight, norm, v_worldPos, viewDir);

	color = vec4(fragColor, 1.0);
};

vec3 calcDirLightCol(DirLight light, vec3 norm, vec3 viewDir)
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse0, v_texCoords));
	vec3 lightDir = normalize(-light.dir);
	float diff = max(dot(lightDir, norm), 0);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse0, v_texCoords));

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
	vec3 specular = spec * light.specular * vec3(texture(material.specular0, v_texCoords));

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
	float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
	vec3 specular = spec * light.specular * vec3(texture(material.specular0, v_texCoords));

	float distance = length(light.pos - worldPos);
	float atten = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	ambient *= atten;
	diffuse *= atten;
	specular *= atten;

	vec3 fragColor = ambient + diffuse + specular;
	return fragColor;
}

vec3 calcSpotLightCol(SpotLight light, vec3 norm, vec3 worldPos, vec3 viewDir)
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse0, v_texCoords));
	vec3 lightDir = normalize(light.pos - worldPos);
	float diff = max(dot(lightDir, norm), 0);
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse0, v_texCoords));

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
	vec3 specular = spec * light.specular * vec3(texture(material.specular0, v_texCoords));

	float theta = dot(lightDir, normalize(-light.dir));
	float epsilon = light.cutOff - light.outterCutOff;
	float intensity = clamp((theta - light.outterCutOff) / epsilon, 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;

	vec3 fragColor = ambient + diffuse + specular;
	return fragColor;
}