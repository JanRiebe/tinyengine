#version 420 core
precision highp float;

uniform sampler2D InputTexture;

in VertexData
{
	vec2 TexCoord;
} inData;

float gauss(const float d, const float sigma)
{
        return exp(-0.5 * (d / sigma) * (d / sigma));
}

out vec3 outColor;
void main(void)
{
	vec3 summedColors = vec3(0.0, 0.0, 0.0);
	float summedWeights = 0.0;
	
	for(int i = -30; i <= 30; i++)
	{
		vec2 readTexCoord = inData.TexCoord;
		readTexCoord.y += float(i) / 512.0;
		vec3 colorSample = texture(InputTexture, readTexCoord).xyz;
		
		float weight = gauss(i, 10);
		summedWeights += weight;
		summedColors += colorSample * weight;
	}

	outColor = summedColors / summedWeights;
}
