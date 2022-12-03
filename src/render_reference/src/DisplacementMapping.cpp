#include "Camera.h"
#include "DirectionalLight.h"
#include "Mesh.h"
#include "Vec3.h"

#include "fileio.h"
#include "gltools.h"
#include "eventhandling.h"

#include <iostream>

using namespace std;

bool finished = false;

int main(int argc, char ** argv)
{
	initGL();

	glClearColor(0, 0, 0, 1);
	GL_CHECK_ERROR();
	glClearDepth(1.0f);
	GL_CHECK_ERROR();
	glEnable(GL_DEPTH_TEST);
	GL_CHECK_ERROR();

	// Create shader
	GLuint shaderProgram = createShaderProgram("Shaders/displacement.vs",
			"Shaders/displacement.tc", "Shaders/displacement.te", NULL,
			"Shaders/displacement.fs");
	glPatchParameteri(GL_PATCH_VERTICES, 3);

	// Create camera and light
	Camera camera(Vec3(0.0f, -3.0f, 3.0f), Vec3(0.0f, 1.0f, -1.0f),
			Vec3(0.0f, 0.0f, 1.0f), 6.0f);
	DirectionalLight light(Vec3(-1.0f, -1.0f, -1.0f), Vec3(1.0f, 1.0f, 1.0f));

	// Load Mesh
	Mesh mesh("Meshes/plane.obj", shaderProgram);

	// Generate and upload textures
	// Create the texture
	unsigned char* texData;
	int resX, resY;
	load_image_ppm("Textures/bricks_diffuse.ppm", &texData, &resX, &resY);
	GLuint texDiffuse;
	glGenTextures(1, &texDiffuse);
	GL_CHECK_ERROR();
	glBindTexture(GL_TEXTURE_2D, texDiffuse);
	GL_CHECK_ERROR();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resX, resY, GL_FALSE, GL_RGB,
			GL_UNSIGNED_BYTE, texData);
	GL_CHECK_ERROR();
	glGenerateMipmap(GL_TEXTURE_2D);
	GL_CHECK_ERROR();
	glBindTexture(GL_TEXTURE_2D, 0);
	GL_CHECK_ERROR();
	delete[] texData;

	load_image_ppm("Textures/bricks_normal.ppm", &texData, &resX, &resY);
	GLuint texNormal;
	glGenTextures(1, &texNormal);
	GL_CHECK_ERROR();
	glBindTexture(GL_TEXTURE_2D, texNormal);
	GL_CHECK_ERROR();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resX, resY, GL_FALSE, GL_RGB,
			GL_UNSIGNED_BYTE, texData);
	GL_CHECK_ERROR();
	glGenerateMipmap(GL_TEXTURE_2D);
	GL_CHECK_ERROR();
	glBindTexture(GL_TEXTURE_2D, 0);
	GL_CHECK_ERROR();
	delete[] texData;

	load_image_ppm("Textures/bricks_displacement.ppm", &texData, &resX, &resY);
	GLuint texDisplacement;
	glGenTextures(1, &texDisplacement);
	GL_CHECK_ERROR();
	glBindTexture(GL_TEXTURE_2D, texDisplacement);
	GL_CHECK_ERROR();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, resX, resY, GL_FALSE, GL_RGB,
			GL_UNSIGNED_BYTE, texData);
	GL_CHECK_ERROR();
	glGenerateMipmap(GL_TEXTURE_2D);
	GL_CHECK_ERROR();
	glBindTexture(GL_TEXTURE_2D, 0);
	GL_CHECK_ERROR();
	delete[] texData;

	// Create and configure the texture sampler
	GLuint sampler;
	glGenSamplers(1, &sampler);
	GL_CHECK_ERROR();
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	GL_CHECK_ERROR();
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	GL_CHECK_ERROR();
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GL_CHECK_ERROR();
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR);
	GL_CHECK_ERROR();

	// Draw
	__int64_t lastFrameStart = continuousTimeNs();
	__int64_t currentFrameStart = continuousTimeNs();
	float time = 0.0f;
	while (!finished)
	{
		lastFrameStart = currentFrameStart;
		currentFrameStart = continuousTimeNs();
		float duration = (currentFrameStart - lastFrameStart) / 1000000000.0f;
		time += duration;

		light.Direction = Vec3(sinf(time), cosf(time), -1.0);
		light.Direction.normalize();

		eventHandling(&camera);
		camera.Move(duration);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GL_CHECK_ERROR();
		glUseProgram(shaderProgram);
		GL_CHECK_ERROR();

		glActiveTexture(GL_TEXTURE0);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, texDiffuse);
		GL_CHECK_ERROR();
		glBindSampler(0, sampler);
		GL_CHECK_ERROR();
		glUniform1i(glGetUniformLocation(shaderProgram, "TexDiffuse"), 0);
		GL_CHECK_ERROR();

		glActiveTexture(GL_TEXTURE1);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, texNormal);
		GL_CHECK_ERROR();
		glBindSampler(1, sampler);
		GL_CHECK_ERROR();
		glUniform1i(glGetUniformLocation(shaderProgram, "TexNormal"), 1);
		GL_CHECK_ERROR();

		glActiveTexture(GL_TEXTURE2);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, texDisplacement);
		GL_CHECK_ERROR();
		glBindSampler(2, sampler);
		GL_CHECK_ERROR();
		glUniform1i(glGetUniformLocation(shaderProgram, "TexDisplacement"), 2);
		GL_CHECK_ERROR();

		camera.ConfigureShaderProgram(shaderProgram, mesh.WorldMatrix);
		light.ConfigureShaderProgram(shaderProgram, camera.GetViewMatrix());
		mesh.Draw(GL_PATCHES);

		glActiveTexture(GL_TEXTURE2);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, 0);
		GL_CHECK_ERROR();

		glActiveTexture(GL_TEXTURE1);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, 0);
		GL_CHECK_ERROR();

		glActiveTexture(GL_TEXTURE0);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, 0);
		GL_CHECK_ERROR();

		glBindSampler(0, 0);
		GL_CHECK_ERROR();
		glUseProgram(0);
		GL_CHECK_ERROR();
		glXSwapBuffers(display, win);
		GL_CHECK_ERROR();
	}

	cout << "Exiting..." << endl;

	// Cleanup
	glDeleteProgram(shaderProgram);
	GL_CHECK_ERROR();
	glDeleteTextures(1, &texDiffuse);
	GL_CHECK_ERROR();
	glDeleteSamplers(1, &sampler);
	GL_CHECK_ERROR();

	exitGL();
}
