#version 420 core
in vec3 inPosition;

uniform mat4 ModelLightMatrix;

void main(void)
{	
	vec3 LightSpacePosition = vec3(ModelLightMatrix * vec4(inPosition, 1.0));
	
	gl_Position.x = LightSpacePosition.x / 5.0f; // x positions between -5 and 5 will be in the output.
	gl_Position.y = LightSpacePosition.z / 5.0f; // y positions between -5 and 5 will be in the output.
	gl_Position.z = LightSpacePosition.y / 10.0f; // z Values between 0 and 10 will be valid for depth testing.
	gl_Position.w = 1.0; // No perspective division: Directional light!	
}
