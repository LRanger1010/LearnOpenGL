#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 aTexCoords;
out vec2 v_texCoords;
uniform mat4 u_MVP;
void main()
{
	gl_Position = u_MVP * position;
	v_texCoords = aTexCoords;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec2 v_texCoords;
uniform sampler2D u_Texture;
void main()
{
	color = texture(u_Texture, v_texCoords);
};