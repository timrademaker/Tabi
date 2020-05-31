#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec4 vertexColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	vertexColor = vec4((aNormal.x + 1.0) / 2.0, (aNormal.y + 1.0) / 2.0, (aNormal.z + 1.0) / 2.0, 1.0);
}