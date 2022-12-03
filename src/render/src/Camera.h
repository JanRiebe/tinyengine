#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "Matrix4x4.h"

#include "gltools.h"

class Camera
{
	Vec3 eye, right, direction, up, worldUp;
	float focalLength;
	float nearPlane;
	float farPlane;
	float speed;

	float rotX, rotY;
	int action;
public:
	/**
	 * Initializes a camera.
	 * @param eye Camera's position.
	 * @param direction Viewing direction.
	 * @param worldUp Up direction in the world space. Should be (0, 0, 1).
	 * @param speed Movement speed in world units per second.
	 */
	Camera(const Vec3 &eye, const Vec3 &direction, const Vec3 &worldUp,
			const float speed);

	virtual ~Camera();

	/**
	 * Returns a view matrix according to the current settings.
	 * @returns Current view matrix.
	 */
	Matrix4x4 GetViewMatrix();
	/**
	 * Returns the current viewing direction.
	 * @returns Current Viewing Direction.
	 */
	Vec3 GetDirection();
	/**
	 * Configures uniform variables of the currently bound shader program
	 * to make it rendering according to this camera's parameters.
	 * @remarks The currently bound shader program must expose the following
	 * variables:
	 * <ul>
	 *  <li>uniform mat4 ViewMatrix;</li>
	 *  <li>uniform float FocalLength;</li>
	 *  <li>uniform float MinDepth;</li>
	 *  <li>uniform float MaxDepth;</li>
	 * </ul>
	 * @param shaderProgram Currently bound shader program. Is used to find
	 * the uniform variable shader locations.
	 */
	void ConfigureShaderProgram(const GLuint shaderProgram,
			const Matrix4x4 &worldMatrix);
	/**
	 * Transformes the accumulated scalar movement information available to
	 * a new parameter set.
	 * @param time Time that has been gone since the last call to SetupView on the
	 * same viewport. This parameter is used to calculate the movement distances.
	 */
	void Move(const float time);

	void MoveForward(const bool b);
	void MoveBackward(const bool b);
	void MoveLeft(const bool b);
	void MoveRight(const bool b);
	void RotateX(const float rx);
	void RotateY(const float ry);
};

inline void Camera::MoveForward(const bool b)
{
	action = b ? action | 1 : action & ~1;
}

inline void Camera::MoveBackward(const bool b)
{
	action = b ? action | 2 : action & ~2;
}

inline void Camera::MoveLeft(const bool b)
{
	action = b ? action | 4 : action & ~4;
}

inline void Camera::MoveRight(const bool b)
{
	action = b ? action | 8 : action & ~8;
}

inline void Camera::RotateX(const float rx)
{
	rotX -= rx;
}

inline void Camera::RotateY(const float ry)
{
	rotY -= ry;
}

#endif

