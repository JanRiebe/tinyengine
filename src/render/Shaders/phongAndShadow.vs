#version 420 core
in vec3 inPosition;
in vec3 inNormal;

out VertexData
{
	vec3 ViewPosition;
	vec3 Normal;
	vec2 TexCoords;
	float LightSpaceDepth;
} outData;

uniform mat4 ModelViewMatrix;
uniform float FocalLength;
uniform float MinDepth;
uniform float MaxDepth;

uniform mat4 ModelLightMatrix;

vec4 perspectiveTransform(vec4 viewPosition)
{
	viewPosition.w = viewPosition.y; // Have the depth in w
	viewPosition.y = viewPosition.z; // Have the up-component in y
	// Have the distance scaled to (0..maxDepth) in z (homogenous division scales down to 0..1)
	viewPosition.z = (viewPosition.w - MinDepth) * MaxDepth / (MaxDepth - MinDepth);
	viewPosition.x *= FocalLength; // Incease magification with high image plane distance
	viewPosition.y *= FocalLength; // Incease magification with high image plane distance
	return viewPosition;
}

void main(void)
{	
	outData.ViewPosition = vec3(ModelViewMatrix * vec4(inPosition, 1.0));
	gl_Position = perspectiveTransform(vec4(outData.ViewPosition, 1.0));
	
	// Transform the vertex position to light space for depth map comparison
	vec3 LightSpacePosition = vec3(ModelLightMatrix * vec4(inPosition, 1.0));
	
	// Calculate the depth value comparable to the light's depth map
	outData.LightSpaceDepth = LightSpacePosition.y / 10.0f;
	// The following transformation corresponds to the 
	// default OpenGL viewport transformation
	outData.LightSpaceDepth = 0.5 + 0.5 * outData.LightSpaceDepth;
	
	// Calculate the texture coordinates that correspond to the 
	// light space position
	outData.TexCoords.x = LightSpacePosition.x / 10.0f + 0.5f;
	outData.TexCoords.y = LightSpacePosition.z / 10.0f + 0.5f;

	outData.Normal = mat3(ModelViewMatrix) * inNormal;
}
