#include "ImagePlaneMesh.h"

#include "Vec3.h"

#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

struct Vec2
{
	float x;
	float y;

	Vec2()
	{
	}

	Vec2(const float x, const float y) :
			x(x), y(y)
	{
	}
};

struct Face
{
	Face(const unsigned int idx1, const unsigned int idx2,
			const unsigned int idx3)
	{
		idxs[0] = idx1;
		idxs[1] = idx2;
		idxs[2] = idx3;
	}

	unsigned int idxs[3];
};

ImagePlaneMesh::ImagePlaneMesh(const GLuint shaderProgram) :
		WorldMatrix(Matrix4x4::Identity)
{
	vector<Vec2> positions;
	vector<Vec2> texCoords; // one tex coord per position
	vector<Face> faces;

	// Define the mesh
	positions.push_back(Vec2(-1.0, 1.0));
	positions.push_back(Vec2(1.0, 1.0));
	positions.push_back(Vec2(-1.0, -1.0));
	positions.push_back(Vec2(1.0, -1.0));

	texCoords.push_back(Vec2(0.0f, 1.0f));
	texCoords.push_back(Vec2(1.0f, 1.0f));
	texCoords.push_back(Vec2(0.0f, 0.0f));
	texCoords.push_back(Vec2(1.0f, 0.0f));

	faces.push_back(Face(0, 1, 2));
	faces.push_back(Face(1, 3, 2));

	// Setup GL mesh
	glGenBuffers(1, &positionBuffer);
	GL_CHECK_ERROR();
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	GL_CHECK_ERROR();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * positions.size(),
			&positions[0], GL_STATIC_DRAW);
	GL_CHECK_ERROR();

	glGenBuffers(1, &texCoordBuffer);
	GL_CHECK_ERROR();
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	GL_CHECK_ERROR();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * texCoords.size(),
			&texCoords[0], GL_STATIC_DRAW);
	GL_CHECK_ERROR();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL_CHECK_ERROR();

	glGenVertexArrays(1, &vertexArrayObject);
	GL_CHECK_ERROR();
	glBindVertexArray(vertexArrayObject);
	GL_CHECK_ERROR();

	if (glGetAttribLocation(shaderProgram, "inPosition") != -1)
	{
		GL_CHECK_ERROR();
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		GL_CHECK_ERROR();
		glEnableVertexAttribArray(
				glGetAttribLocation(shaderProgram, "inPosition"));
		GL_CHECK_ERROR();
		glVertexAttribPointer(glGetAttribLocation(shaderProgram, "inPosition"),
				2, GL_FLOAT, GL_FALSE, 0, 0);
		GL_CHECK_ERROR();
	}

	if (glGetAttribLocation(shaderProgram, "inTexCoord") != -1)
	{
		GL_CHECK_ERROR();
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		GL_CHECK_ERROR();
		glEnableVertexAttribArray(
				glGetAttribLocation(shaderProgram, "inTexCoord"));
		GL_CHECK_ERROR();
		glVertexAttribPointer(glGetAttribLocation(shaderProgram, "inTexCoord"),
				2, GL_FLOAT, GL_FALSE, 0, 0);
		GL_CHECK_ERROR();
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL_CHECK_ERROR();
	glBindVertexArray(0);
	GL_CHECK_ERROR();

	// Upload indices...
	glGenBuffers(1, &elementArrayBuffer);
	GL_CHECK_ERROR();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);
	GL_CHECK_ERROR();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * faces.size() * 3,
			&faces[0], GL_STATIC_DRAW);
	GL_CHECK_ERROR();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GL_CHECK_ERROR();

	numIndices = faces.size() * 3;
}

ImagePlaneMesh::~ImagePlaneMesh()
{
	glDeleteBuffers(1, &elementArrayBuffer);
	GL_CHECK_ERROR();
	glDeleteVertexArrays(1, &vertexArrayObject);
	GL_CHECK_ERROR();
	glDeleteBuffers(1, &texCoordBuffer);
	GL_CHECK_ERROR();
	glDeleteBuffers(1, &positionBuffer);
	GL_CHECK_ERROR();
}

void ImagePlaneMesh::Draw(GLenum mode)
{
	glBindVertexArray(vertexArrayObject);
	GL_CHECK_ERROR();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArrayBuffer);
	GL_CHECK_ERROR();

	glDrawElements(mode, numIndices, GL_UNSIGNED_INT, 0);
	GL_CHECK_ERROR();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GL_CHECK_ERROR();
	glBindVertexArray(0);
	GL_CHECK_ERROR();
}
