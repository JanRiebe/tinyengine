#ifndef IMAGEPLANEMESH_H_
#define IMAGEPLANEMESH_H_

#include "gltools.h"
#include "Matrix4x4.h"

class ImagePlaneMesh
{
	GLuint positionBuffer;
	GLuint texCoordBuffer;
	GLuint normalBuffer;
	GLuint tangent1Buffer;
	GLuint tangent2Buffer;

	GLuint vertexArrayObject;
	GLuint elementArrayBuffer;

	unsigned int numIndices;

public:
	Matrix4x4 WorldMatrix;

	ImagePlaneMesh(const GLuint shaderProgram);
	virtual ~ImagePlaneMesh();

	void Draw(GLenum mode);
};

#endif /* IMAGEPLANEMESH_H_ */
