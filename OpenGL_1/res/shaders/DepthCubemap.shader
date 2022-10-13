#shader vertex
#version 330 core
layout(location = 0) in vec4 position;

uniform mat4 u_Model;
void main()
{
	gl_Position = u_Model * position;
};

#shader geometry
#version 330 core
layout(triangles) in;
layout(triangles_strip, max_vertices = 18) out;
in vec3 v_normal[];
uniform mat4 u_Projection;
const float MAGNITUDE = 0.4;

void GenerateLine(int index)
{
	gl_Position = u_Projection * gl_in[index].gl_Position;
	EmitVertex();
	gl_Position = u_Projection * (gl_in[index].gl_Position + vec4(v_normal[index], 0.0) * MAGNITUDE);
	EmitVertex();
	EndPrimitive();
};

void main()
{
	GenerateLine(0);
	GenerateLine(1);
	GenerateLine(2);
};

#shader fragment
#version 330 core


void main()
{
	
};