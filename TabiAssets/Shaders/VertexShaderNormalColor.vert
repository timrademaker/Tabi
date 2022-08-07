#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

layout(binding = 0) uniform InData
{
	mat4 cameraTransform;
};

layout(binding = 1) uniform ModelData
{
	mat4 modelMatrix;
	vec4 baseColorFactor;
};

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

layout(location = 0) out vec4 vertexColor;

void main()
{
	gl_Position = cameraTransform * modelMatrix * vec4(aPos, 1.0);
	vertexColor = vec4((aNormal.x + 1.0) / 2.0, (aNormal.y + 1.0) / 2.0, (aNormal.z + 1.0) / 2.0, 1.0);
}
