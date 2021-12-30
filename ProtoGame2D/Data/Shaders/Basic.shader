#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 posColor;
layout(location = 2) in vec2 texCoord;

out vec4 v_PosColor;
out vec2 v_TexCoord;

uniform mat4 u_Proj;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Proj * u_Model * position;
	v_PosColor = posColor;
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

out vec4 FragColor;

in vec4 v_PosColor;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	vec4 texel = texture(u_Texture, v_TexCoord);

	FragColor = texel * v_PosColor;
};