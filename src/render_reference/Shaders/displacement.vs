#version 420 core
in vec3 inPosition;
in vec2 inTexCoord;
in vec3 inNormal;
in vec3 inTangent1;
in vec3 inTangent2;

uniform mat4 ModelViewMatrix;

out VertexData
{
	vec3 Tangent1;
	vec3 Tangent2;
	vec3 Normal;
	vec2 TexCoords;
} outData;

void main(void)
{
	gl_Position = ModelViewMatrix * vec4(inPosition, 1.0);
	outData.TexCoords = inTexCoord;
	
	outData.Tangent1 = mat3(ModelViewMatrix) * inTangent1;
	outData.Tangent2 = mat3(ModelViewMatrix) * inTangent2;
	outData.Normal = mat3(ModelViewMatrix) * inNormal;
}
