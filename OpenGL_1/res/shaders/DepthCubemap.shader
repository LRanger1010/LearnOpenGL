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
layout(triangle_strip, max_vertices = 18) out;
uniform mat4 u_LightMatrix[6];
out vec4 v_worldPos;

void main()
{
	for (int face = 0; face < 6; face++)
	{
		gl_Layer = face;
		for (int i = 0; i < 3; i++)
		{
			v_worldPos = gl_in[i].gl_Position;
			gl_Position = u_LightMatrix[face] * v_worldPos;
			EmitVertex();
		}
		EndPrimitive();
	}
};

#shader fragment
#version 330 core
in vec4 v_worldPos;
uniform vec3 u_LightPos;
uniform float u_FarPlane;

void main()
{
	float distance = length(u_LightPos - v_worldPos.xyz);
	distance = distance / u_FarPlane;
	gl_FragDepth = distance;
};