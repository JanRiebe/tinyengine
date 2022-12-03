#ifndef MESH_H_
#define MESH_H_

#include "gltools.h"
#include "Matrix4x4.h"

class Mesh
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

	Mesh(const char* filename, const GLuint shaderProgram);
	virtual ~Mesh();

	void Draw(GLenum mode);
};

#endif /* MESH_H_ */
