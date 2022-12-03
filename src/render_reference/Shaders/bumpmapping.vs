#version 420 core
in vec3 inPosition;
in vec2 inTexCoord;
in vec3 inNormal;
in vec3 inTangent1;
in vec3 inTangent2;

out VertexData
{
	vec3 Tangent1;
	vec3 Tangent2;
	vec3 Normal;
	vec2 TexCoords;
} outData;

uniform mat4 ModelViewMatrix;
uniform float FocalLength;
uniform float MinDepth;
uniform float MaxDepth;

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
	gl_Position = perspectiveTransform(ModelViewMatrix * vec4(inPosition, 1.0));
	outData.TexCoords = inTexCoord;
	
	outData.Tangent1 = mat3(ModelViewMatrix) * inTangent1;
	outData.Tangent2 = mat3(ModelViewMatrix) * inTangent2;
	outData.Normal = mat3(ModelViewMatrix) * inNormal;
}
