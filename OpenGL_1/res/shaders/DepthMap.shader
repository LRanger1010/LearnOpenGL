#shader vertex
#version 330 core
layout(location = 0) in vec4 position;

uniform mat4 u_Model;
uniform mat4 u_LightMatrix;
void main()
{
	gl_Position = u_LightMatrix * u_Model * position;
};

#shader fragment
#version 330 core


void main()
{
	
};