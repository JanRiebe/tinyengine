#version 420 core

uniform vec3 LightDirection;
uniform vec3 LightColor;

uniform sampler2DShadow ShadowMap;

in VertexData
{
	vec3 Normal;
	vec2 TexCoords;
	float LightSpaceDepth;
} inData;

out vec3 outColor;
void main(void)
{
	// Calculate the diffuse brightness
	vec3 Normal = normalize(inData.Normal);
	vec3 diffuse = LightColor * max(0.0, dot(Normal, -LightDirection));
	
	// If the texture sampler is set up for depth comparison,
	// calling the texture(...) function with a sampler2DShadow
	// compares the value stored in the texture against the 
	// 3rd texture coordinate component	
	float shadowColor = texture(ShadowMap, vec3(inData.TexCoords, inData.LightSpaceDepth - 0.005)).x;
	
	// Final fragment color
	outColor = diffuse * shadowColor;
}
