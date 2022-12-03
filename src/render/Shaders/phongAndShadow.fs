#version 420 core

uniform vec3 LightDirection;
uniform vec3 LightColor;

vec3 DiffuseColor = vec3(0.2, 0.0, 1.0);
vec3 SpecularColor = vec3(100.0, 100.0, 100.0);

uniform sampler2DShadow ShadowMap;

in VertexData
{
	vec3 ViewPosition;
	vec3 Normal;
	vec2 TexCoords;
	float LightSpaceDepth;
} inData;

out vec4 outColor;
void main(void)
{
	vec3 toViewer = normalize(-inData.ViewPosition);
	vec3 toLight = normalize(-LightDirection);
	
	vec3 halfVector = normalize(toViewer + toLight);
	
	vec3 normal = normalize(inData.Normal);

	vec3 diffuse = DiffuseColor * LightColor * max(0.0, dot(normal, -LightDirection));
	vec3 specular = SpecularColor * LightColor * max(0.0, pow(dot(halfVector, normal), 1000.0));
	
	// If the texture sampler is set up for depth comparison,
	// calling the texture(...) function with a sampler2DShadow
	// compares the value stored in the texture against the 
	// 3rd texture coordinate component	
	float shadowColor = texture(ShadowMap, vec3(inData.TexCoords, inData.LightSpaceDepth - 0.005)).x;
	
	outColor = vec4((diffuse + specular) * shadowColor, 1.0);

}
