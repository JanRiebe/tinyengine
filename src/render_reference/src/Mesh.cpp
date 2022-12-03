#include "Mesh.h"

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

Mesh::Mesh(const char* filename, const GLuint shaderProgram) :
		WorldMatrix(Matrix4x4::Identity)
{
	vector<Vec3> positions;
	vector<Vec2> readTexCoords; // every tex coord just once
	vector<Vec2> texCoords; // one tex coord per position
	vector<Vec3> readNormals; // every normal just once
	vector<Vec3> normals; // one normal per position
	vector<Face> faces;

	// Read positions, tex coords, normals and indices
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Could not open obj file!" << endl;
		exit(1);
	}
	string line;
	while (!file.eof())
	{
		getline(file, line);
		if (line.length() == 0)
			continue;

		string lineType;
		if (line[0] == '#')
			lineType = string("#");
		else
			lineType = line.substr(0, line.find_first_of(' '));

		if (lineType.compare("v") == 0)
		{
			Vec3 position;
			sscanf(line.c_str(), "v %f %f %f", &position.x, &position.y,
					&position.z);
			positions.push_back(position);
		}
		else if (lineType.compare("vt") == 0)
		{
			Vec2 texCoord;
			sscanf(line.c_str(), "vt %f %f", &texCoord.x, &texCoord.y);
			texCoord.y = 1.0f - texCoord.y;
			readTexCoords.push_back(texCoord);
		}
		else if (lineType.compare("vn") == 0)
		{
			Vec3 normal;
			sscanf(line.c_str(), "vn %f %f %f", &normal.x, &normal.y,
					&normal.z);
			readNormals.push_back(normal);
		}
		else if (lineType.compare("f") == 0)
		{
			if (normals.size() < positions.size())
				normals.resize(positions.size());
			if (texCoords.size() < positions.size())
				texCoords.resize(positions.size());

			unsigned int posIdxs[3], texCoordIdxs[3], normalIdxs[3];

			sscanf(line.c_str(), "f %u/%u/%u %u/%u/%u %u/%u/%u", &posIdxs[0],
					&texCoordIdxs[0], &normalIdxs[0], &posIdxs[1],
					&texCoordIdxs[1], &normalIdxs[1], &posIdxs[2],
					&texCoordIdxs[2], &normalIdxs[2]);
			// Change from 1-based to 0-based indices
			for (unsigned int i = 0; i < 3; i++)
			{
				posIdxs[i]--;
				normalIdxs[i]--;
				texCoordIdxs[i]--;
			}

			// Generate per position tex coords and normals.
			for (unsigned int i = 0; i < 3; i++)
			{
				texCoords[posIdxs[i]] = readTexCoords[texCoordIdxs[i]];
				normals[posIdxs[i]] = readNormals[normalIdxs[i]];
			}
			faces.push_back(Face(posIdxs[0], posIdxs[1], posIdxs[2]));
		}
	}
	file.close();

	// Calculate tangents
	vector<Vec3> tangents1(positions.size(), Vec3(0.0f, 0.0f, 0.0f));
	vector<Vec3> tangents2(positions.size(), Vec3(0.0f, 0.0f, 0.0f));
	vector<unsigned int> tangentsCount(positions.size(), 0);
	for (unsigned int f = 0; f < faces.size(); f++)
	{
		// Code according to
		// http://www.terathon.com/code/tangent.html

		unsigned int i1 = faces[f].idxs[0];
		unsigned int i2 = faces[f].idxs[1];
		unsigned int i3 = faces[f].idxs[2];

		const Vec3& v1 = positions[i1];
		const Vec3& v2 = positions[i2];
		const Vec3& v3 = positions[i3];

		const Vec2& w1 = texCoords[i1];
		const Vec2& w2 = texCoords[i2];
		const Vec2& w3 = texCoords[i3];

		float x1 = v2.x - v1.x;
		float x2 = v3.x - v1.x;
		float y1 = v2.y - v1.y;
		float y2 = v3.y - v1.y;
		float z1 = v2.z - v1.z;
		float z2 = v3.z - v1.z;

		float s1 = w2.x - w1.x;
		float s2 = w3.x - w1.x;
		float t1 = w2.y - w1.y;
		float t2 = w3.y - w1.y;

		float r = 1.0F / (s1 * t2 - s2 * t1);
		Vec3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
				(t2 * z1 - t1 * z2) * r);
		Vec3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
				(s1 * z2 - s2 * z1) * r);

		tangents1[i1] += sdir;
		tangents1[i2] += sdir;
		tangents1[i3] += sdir;

		tangents2[i1] += tdir;
		tangents2[i2] += tdir;
		tangents2[i3] += tdir;
	}

	for (unsigned int t = 0; t < positions.size(); t++)
	{
		tangents1[t].normalize();
		tangents2[t].normalize();
	}

	// Setup GL mesh
	glGenBuffers(1, &positionBuffer);
	GL_CHECK_ERROR();
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	GL_CHECK_ERROR();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * positions.size(),
			&positions[0], GL_STATIC_DRAW);
	GL_CHECK_ERROR();

	glGenBuffers(1, &texCoordBuffer);
	GL_CHECK_ERROR();
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	GL_CHECK_ERROR();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * texCoords.size(),
			&texCoords[0], GL_STATIC_DRAW);
	GL_CHECK_ERROR();

	glGenBuffers(1, &normalBuffer);
	GL_CHECK_ERROR();
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	GL_CHECK_ERROR();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * normals.size(), &normals[0],
			GL_STATIC_DRAW);
	GL_CHECK_ERROR();

	glGenBuffers(1, &tangent1Buffer);
	GL_CHECK_ERROR();
	glBindBuffer(GL_ARRAY_BUFFER, tangent1Buffer);
	GL_CHECK_ERROR();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * tangents1.size(),
			&tangents1[0], GL_STATIC_DRAW);
	GL_CHECK_ERROR();

	glGenBuffers(1, &tangent2Buffer);
	GL_CHECK_ERROR();
	glBindBuffer(GL_ARRAY_BUFFER, tangent2Buffer);
	GL_CHECK_ERROR();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * tangents2.size(),
			&tangents2[0], GL_STATIC_DRAW);
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
				3, GL_FLOAT, GL_FALSE, 0, 0);
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

	if (glGetAttribLocation(shaderProgram, "inNormal") != -1)
	{
		GL_CHECK_ERROR();
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		GL_CHECK_ERROR();
		glEnableVertexAttribArray(
				glGetAttribLocation(shaderProgram, "inNormal"));
		GL_CHECK_ERROR();
		glVertexAttribPointer(glGetAttribLocation(shaderProgram, "inNormal"), 3,
				GL_FLOAT, GL_FALSE, 0, 0);
		GL_CHECK_ERROR();
	}

	if (glGetAttribLocation(shaderProgram, "inTangent1") != -1)
	{
		GL_CHECK_ERROR();
		glBindBuffer(GL_ARRAY_BUFFER, tangent1Buffer);
		GL_CHECK_ERROR();
		glEnableVertexAttribArray(
				glGetAttribLocation(shaderProgram, "inTangent1"));
		GL_CHECK_ERROR();
		glVertexAttribPointer(glGetAttribLocation(shaderProgram, "inTangent1"),
				3, GL_FLOAT, GL_FALSE, 0, 0);
		GL_CHECK_ERROR();
	}

	if (glGetAttribLocation(shaderProgram, "inTangent2") != -1)
	{
		GL_CHECK_ERROR();
		glBindBuffer(GL_ARRAY_BUFFER, tangent2Buffer);
		GL_CHECK_ERROR();
		glEnableVertexAttribArray(
				glGetAttribLocation(shaderProgram, "inTangent2"));
		GL_CHECK_ERROR();
		glVertexAttribPointer(glGetAttribLocation(shaderProgram, "inTangent2"),
				3, GL_FLOAT, GL_FALSE, 0, 0);
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

Mesh::~Mesh()
{
	glDeleteBuffers(1, &elementArrayBuffer);
	GL_CHECK_ERROR();
	glDeleteVertexArrays(1, &vertexArrayObject);
	GL_CHECK_ERROR();
	glDeleteBuffers(1, &tangent2Buffer);
	GL_CHECK_ERROR();
	glDeleteBuffers(1, &tangent1Buffer);
	GL_CHECK_ERROR();
	glDeleteBuffers(1, &normalBuffer);
	GL_CHECK_ERROR();
	glDeleteBuffers(1, &texCoordBuffer);
	GL_CHECK_ERROR();
	glDeleteBuffers(1, &positionBuffer);
	GL_CHECK_ERROR();
}

void Mesh::Draw(GLenum mode)
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
