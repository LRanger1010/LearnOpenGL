#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aNormal;
out vec3 v_normal;
out vec3 v_worldPos;
uniform mat4 u_Model;
uniform mat4 u_MVP;
uniform mat4 u_NormalMatrix;
void main()
{
	gl_Position = u_MVP * position;
	v_worldPos = vec3(u_Model * position);
	v_normal = mat3(u_NormalMatrix) * aNormal;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec3 v_normal;
in vec3 v_worldPos;
uniform vec3 viewPos;
uniform samplerCube u_Skybox;
uniform float u_refractive_index;

void main()
{
	vec3 norm = normalize(v_normal);
	vec3 viewDir = normalize(viewPos - v_worldPos);
	vec3 refractDir = refract(-viewDir, norm, u_refractive_index);
	vec3 fragColor = texture(u_Skybox, refractDir).rgb;
	color = vec4(fragColor, 1.0);
};