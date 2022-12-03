#version 420 core

uniform vec3 LightDirection;
uniform vec3 LightColor;

vec3 DiffuseColor = vec3(0.2, 0.0, 1.0);
vec3 SpecularColor = vec3(1.0, 1.0, 1.0);
vec3 AmbientColor = vec3(0.2, 0.2, 0.2);

in VertexData
{
	vec3 ViewPosition;
	vec3 Normal;
} inData;

out vec4 outColor;
void main(void)
{
	vec3 toViewer = normalize(-inData.ViewPosition);
	vec3 toLight = normalize(-LightDirection);
	
	vec3 halfVector = normalize(toViewer + toLight);
	
	vec3 normal = normalize(inData.Normal);

	vec3 diffuse = dot(normal, -LightDirection) > 0 ? DiffuseColor : AmbientColor;
	vec3 specular = pow(dot(halfVector, normal), 20.0) > 0.85 ? SpecularColor : vec3(0.0, 0.0, 0.0);
	
	outColor = vec4(diffuse + specular, 1.0);
	
	if(dot(normal, toViewer) < 0.2)
		outColor = vec4(0.0, 0.0, 0.0, 1.0);
}
