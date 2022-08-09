#version 460 core

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec4 aColor;

layout (location = 0) out vec2 Frag_UV;
layout (location = 1) out vec4 Frag_Color;

layout(binding = 0) uniform InData
{
  mat4 ProjectionMatrix;
};

out gl_PerVertex
{
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
};

void main()
{
    Frag_UV = aUV;
    Frag_Color = aColor;
    gl_Position = ProjectionMatrix * vec4(aPosition.xy, 0, 1);
}
