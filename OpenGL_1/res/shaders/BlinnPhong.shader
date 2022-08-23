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
uniform vec3 lightPos;
uniform vec3 viewPos;
void main()
{
	vec3 ambient = lightColor * 0.1;

	vec3 lightDir = normalize(lightPos - v_worldPos);
	vec3 norm = normalize(v_normal);
	float diff = max(dot(lightDir, norm), 0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - v_worldPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0), 32);
	vec3 specular = spec * lightColor;

	vec3 fragColor = (ambient + diffuse + specular) * objectColor;
	color = vec4(fragColor, 1.0);
};