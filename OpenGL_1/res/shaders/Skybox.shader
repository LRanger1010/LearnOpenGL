#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
out vec3 v_texCoords;
uniform mat4 u_MVP;
void main()
{
	gl_Position = (u_MVP * position).xyww;
	v_texCoords = position.xyz;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec3 v_texCoords;
uniform samplerCube u_CubeMap;
void main()
{
	color = texture(u_CubeMap, v_texCoords);
};