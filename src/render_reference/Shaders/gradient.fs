#version 420 core

in VertexData
{
	vec3 ViewPosition;
	vec2 TexCoord;
} inData;

out vec3 outColor;
void main(void)
{
	outColor = vec3(1.0, 1.0, 1.0) * inData.TexCoord.x * 10.0;
}
