#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;

layout(binding = 0) uniform InData
{
	mat4 cameraTransform;
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
	gl_Position = cameraTransform * vec4(aPos, 1.0);
	vertexColor = vec4(aCol, 1.0);
}
