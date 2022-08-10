#version 450 core

layout(location = 0) in vec2 TexCoords;
layout(location = 1) in vec4 BaseColorFactor;

layout(binding = 0) uniform sampler2D uTexture;

out vec4 FragColor;

void main()
{
	FragColor = texture(uTexture, TexCoords) * BaseColorFactor;
}
