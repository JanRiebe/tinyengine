#ifndef DIRECTIONALLIGHT_H_
#define DIRECTIONALLIGHT_H_

#include "Vec3.h"
#include "Matrix4x4.h"

#include "gltools.h"

class DirectionalLight
{
public:
	Vec3 Direction;
	Vec3 Color;

	DirectionalLight(const Vec3& position, const Vec3 color);
	virtual ~DirectionalLight();

	/**
	 * Configures uniform variables of the currently bound shader program
	 * to make it rendering according to this light's parameters.
	 * @remarks The currently bound shader program must expose the following
	 * variables:
	 * <ul>
	 *  <li>uniform vec3 LightDirection;</li>
	 *  <li>uniform vec3 LightColor;</li>
	 * </ul>
	 * @param shaderProgram Currently bound shader program. Is used to find
	 * the uniform variable shader locations.
	 * @param viewMatrix View matrix which is used for rendering. Is used
	 * to transform the light position from world to view space because
	 * light calculations will take place in view space.
	 */
	void ConfigureShaderProgram(GLuint shaderProgram,
			const Matrix4x4 &viewMatrix);
};

#endif /* DIRECTIONALLIGHT_H_ */
