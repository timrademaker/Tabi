#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec4 vertexColor;

uniform mat4 uTransform;
uniform vec4 uBaseColorFactor;

void main()
{
	gl_Position = uTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	vertexColor = uBaseColorFactor;
}