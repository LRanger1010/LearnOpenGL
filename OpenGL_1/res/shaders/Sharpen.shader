#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 aTexCoords;
out vec2 v_texCoords;
void main()
{
	gl_Position = position;
	v_texCoords = aTexCoords;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec2 v_texCoords;
uniform sampler2D u_Texture;

const float offset = 1.0 / 300.0;

const vec2 offsets[9] = vec2[](
    vec2(-offset, offset), // ����
    vec2(0.0f, offset), // ����
    vec2(offset, offset), // ����
    vec2(-offset, 0.0f),   // ��
    vec2(0.0f, 0.0f),   // ��
    vec2(offset, 0.0f),   // ��
    vec2(-offset, -offset), // ����
    vec2(0.0f, -offset), // ����
    vec2(offset, -offset)  // ����
);

const float kernel[9] = float[](
    -1, -1, -1,
    -1, 9, -1,
    -1, -1, -1
);
void main()
{
    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(u_Texture, v_texCoords + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    color = vec4(col, 1.0);
};