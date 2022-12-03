#version 420 core
in vec3 inPosition;

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
}
