#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Vec3& position, const Vec3 color) :
		Direction(position), Color(color)
{
	Direction.normalize();
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::ConfigureShaderProgram(GLuint shaderProgram,
		const Matrix4x4 &viewMatrix)
{
	Vec3 viewSpaceDirection = viewMatrix.TransformDirection(Direction);

	glUniform3fv(glGetUniformLocation(shaderProgram, "LightDirection"), 1,
			&viewSpaceDirection.x);
	GL_CHECK_ERROR();

	glUniform3fv(glGetUniformLocation(shaderProgram, "LightColor"), 1,
			&Color.x);
	GL_CHECK_ERROR();
}

