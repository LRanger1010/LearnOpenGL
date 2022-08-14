#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in float aTexIndex;
out vec2 v_texCoords;
out float v_texIndex;
uniform mat4 u_MVP;
void main()
{
	gl_Position = u_MVP * position;
	v_texCoords = aTexCoords;
	v_texIndex = aTexIndex;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec2 v_texCoords;
in float v_texIndex;
uniform sampler2D u_Textures[2];
void main()
{
	int index = int(v_texIndex);
	color = texture(u_Textures[index], v_texCoords);
};