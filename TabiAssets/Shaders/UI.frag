#version 460 core

layout(location = 0) in vec2 texCoords;
layout(binding = 0) uniform sampler2D tex;

out vec4 FragColor;

void main()
{
	FragColor = texture(tex, texCoords);
}
