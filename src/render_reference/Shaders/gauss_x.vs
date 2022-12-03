#version 420 core
in vec2 inPosition;
in vec2 inTexCoord;

out VertexData
{
	vec2 TexCoord;
} outData;

void main(void)
{	
	gl_Position = vec4(inPosition, 0.0, 1.0);

	outData.TexCoord = inTexCoord;
}
