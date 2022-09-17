#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
out vec3 v_normal;
uniform mat4 u_Model;
uniform mat4 u_View;
void main()
{
	gl_Position = u_View * u_Model * vec4(aPos, 1.0);
	v_normal = normalize(vec3(vec4(mat3(transpose(inverse(u_View * u_Model))) * aNormal, 0.0)));
};

#shader geometry
#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;
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
out vec4 FragColor;
void main()
{
	FragColor = vec4(1.0, 1.0, 0.0, 1.0);
};