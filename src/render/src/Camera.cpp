#include "Camera.h"

Camera::Camera(const Vec3 &eye, const Vec3 &direction, const Vec3 &worldUp,
		const float speed) :
		eye(eye), direction(direction), worldUp(worldUp), speed(speed)
{
	// Calculate all parameters for a view matrix
	this->direction.normalize();
	this->worldUp.normalize();
	right = Vec3::cross(this->direction, this->worldUp);
	right.normalize();
	up = Vec3::cross(right, this->direction);
	up.normalize();

	// Calculate/initialize all the parameters needed for the projection
	focalLength = 2.0f;
	nearPlane = 1.0f;
	farPlane = 1000.0f;

	// Initialize variables for accumulating movement.
	rotX = 0.0f;
	rotY = 0.0f;
	action = 0;
}

Camera::~Camera()
{
}

Matrix4x4 Camera::GetViewMatrix()
{
	Matrix4x4 viewMatrix(Matrix4x4::Identity);
	viewMatrix._00 = right.x, viewMatrix._01 = right.y, viewMatrix._02 = right.z;
	viewMatrix._10 = direction.x, viewMatrix._11 = direction.y, viewMatrix._12 =
			direction.z;
	viewMatrix._20 = up.x, viewMatrix._21 = up.y, viewMatrix._22 = up.z;
	viewMatrix = viewMatrix * Matrix4x4::Translation(-eye);

	return viewMatrix;
}

Vec3 Camera::GetDirection()
{
	return direction;
}

void Camera::ConfigureShaderProgram(const GLuint shaderProgram,
		const Matrix4x4 &worldMatrix)
{
	// Upload view matrix
	Matrix4x4 modelViewMatrix = GetViewMatrix() * worldMatrix;

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "ModelViewMatrix"),
			1, true, &modelViewMatrix._00);
	GL_CHECK_ERROR();

	// Upload other variables
	glUniform1f(glGetUniformLocation(shaderProgram, "FocalLength"),
			focalLength);
	GL_CHECK_ERROR();

	glUniform1f(glGetUniformLocation(shaderProgram, "MinDepth"), nearPlane);
	GL_CHECK_ERROR();

	glUniform1f(glGetUniformLocation(shaderProgram, "MaxDepth"), farPlane);
	GL_CHECK_ERROR();
}

void Camera::Move(const float time)
{
	if (!(action || rotX != 0.0f || rotY != 0.0f))
		return;

	// Add the rotation information
	Matrix4x4 oldRotation(Matrix4x4::Identity);
	oldRotation._00 = right.x, oldRotation._01 = right.y, oldRotation._02 =
			right.z;
	oldRotation._10 = direction.x, oldRotation._11 = direction.y, oldRotation._12 =
			direction.z;
	oldRotation._20 = up.x, oldRotation._21 = up.y, oldRotation._22 = up.z;
	oldRotation.Transpose();
	Matrix4x4 preUpDown(Matrix4x4::RotationX(rotX));
	Matrix4x4 postLeftRight(Matrix4x4::RotationZ(rotY));
	Matrix4x4 newRotation(postLeftRight * oldRotation * preUpDown);
	direction = newRotation * Vec3(0.0f, 1.0f, 0.0f);
	direction.normalize();
	right = Vec3::cross(direction, worldUp);
	right.normalize();
	up = Vec3::cross(right, direction);
	up.normalize();

	rotX = 0.0f;
	rotY = 0.0f;

	// Add the movement information
	if (action & 1)
		eye += direction * speed * time;
	if (action & 2)
		eye -= direction * speed * time;
	if (action & 4)
		eye -= right * speed * time;
	if (action & 8)
		eye += right * speed * time;
}
