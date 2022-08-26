#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
out vec3 v_normal;
out vec3 v_worldPos;
out vec2 v_texCoords;
uniform mat4 u_Model;
uniform mat4 u_MVP;
void main()
{
	gl_Position = u_MVP * position;
	v_worldPos = vec3(u_Model * position);
	v_normal = aNormal;
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
uniform PointLight pointLight;

struct SpotLight
{
	vec3 pos;
	vec3 dir;
	float cutOff;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform SpotLight spotLight;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
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
	float spec = pow(max(dot(reflectDir, viewDir), 0), material.shininess);
	vec3 specular = spec * light.specular * material.specular;

	vec3 fragColor = ambient + diffuse + specular;
	color = vec4(fragColor, 1.0);
};