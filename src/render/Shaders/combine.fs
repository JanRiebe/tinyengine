#version 420 core

uniform sampler2D OriginalImage;
uniform sampler2D BlurredImage;

in VertexData
{
	vec2 TexCoord;
} inData;

out vec3 outColor;
void main(void)
{
	vec3 originalColor = texture(OriginalImage, inData.TexCoord).xyz;
	vec3 blurredColor = texture(BlurredImage, inData.TexCoord).xyz;

	outColor = 0.7 * originalColor + 0.3 * blurredColor;
}
