#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
out vec3 v_normal;
out vec3 v_worldPos;
out vec2 v_texCoords;
out vec4 v_lightSpacePos;
uniform mat4 u_Model;
uniform mat4 u_MVP;
uniform mat4 u_LightMatrix;
void main()
{
	gl_Position = u_MVP * position;
	v_worldPos = vec3(u_Model * position);
	v_normal = aNormal;
	v_texCoords = aTexCoords;
	v_lightSpacePos = u_LightMatrix * vec4(v_worldPos, 1.0);
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec3 v_normal;
in vec3 v_worldPos;
in vec2 v_texCoords;
in vec4 v_lightSpacePos;
uniform vec3 u_ViewPos;
uniform bool u_ShadowCast;
uniform float farPlane;

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

struct Material
{
	sampler2D diffuse;
	sampler2D shadowMap;
	sampler2D shadowCubemap;
	float shininess;
};
uniform Material material;

float generateDirLightShadow(vec3 lightDir, vec3 norm)
{
	vec3 projCoords = v_lightSpacePos.xyz / v_lightSpacePos.w;
	projCoords = projCoords * 0.5 + 0.5;
	vec2 texelSize = 1.0 / textureSize(material.shadowMap, 0);
	float curDepth = projCoords.z;
	float bias = max(0.05 * (1.0 - dot(lightDir, norm)), 0.005);
	float shadow = 0.0;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			float pcfDepth = texture(material.shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += pcfDepth < curDepth - bias ? 1.0 : 0.0;
		}
	}
	shadow /= 9.0;


	return shadow;
};

float generatePointLightShadow(vec3 worldPos, vec3 lightPos, vec3 norm)
{
	vec3 lightDir = worldPos - lightPos;
	float sampleDepth = texture(material.shadowCubemap, lightDir).r;
	float curDepth = length(lightDir) / farPlane;
	float bias = max(0.05 * (1.0 - dot(normalize(-lightDir), norm)), 0.005);
	float shadow = curDepth - bias > sampleDepth ? 1.0 : 0.0;
	return shadow;
};

vec3 calcDirLightCol(DirLight light, vec3 norm, vec3 viewDir, vec3 materialColor)
{
	vec3 ambient = light.ambient * materialColor;

	vec3 lightDir = normalize(-light.dir);
	float diff = max(dot(lightDir, norm), 0);
	vec3 diffuse = diff * light.diffuse * materialColor;

	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(halfDir, norm), 0), material.shininess);
	vec3 specular = spec * light.specular * materialColor;

	float shadow = u_ShadowCast ? generateDirLightShadow(lightDir, norm) : 0.0;
	vec3 fragColor = ambient + (1.0 - shadow) * (diffuse + specular);
	return fragColor;
};

vec3 calcPointLightCol(PointLight light, vec3 norm, vec3 worldPos, vec3 viewDir, vec3 materialColor)
{
	vec3 ambient = light.ambient * materialColor;

	vec3 lightDir = normalize(light.pos - worldPos);
	float diff = max(dot(lightDir, norm), 0);
	vec3 diffuse = diff * light.diffuse * materialColor;

	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(halfDir, norm), 0), material.shininess);
	vec3 specular = spec * light.specular * materialColor;

	float distance = length(light.pos - worldPos);
	float atten = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
	ambient *= atten;
	diffuse *= atten;
	specular *= atten;

	float shadow = u_ShadowCast ? generatePointLightShadow(worldPos, light.pos, norm) : 0.0;
	vec3 fragColor = ambient + (1.0 - shadow) * (diffuse + specular);
	return fragColor;
};

void main()
{
	vec3 materialColor = vec3(texture(material.diffuse, v_texCoords));
	vec3 norm = normalize(v_normal);
	vec3 viewDir = normalize(u_ViewPos - v_worldPos);
	vec3 fragColor = calcDirLightCol(dirLight, norm, viewDir, materialColor);
	fragColor += calcPointLightCol(pointLight, norm, v_worldPos, viewDir, materialColor);
	color = vec4(fragColor, 1.0);
};