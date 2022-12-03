#include "Camera.h"
#include "DirectionalLight.h"
#include "Mesh.h"
#include "ImagePlaneMesh.h"
#include "Vec3.h"

#include "fileio.h"
#include "gltools.h"
#include "eventhandling.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

bool finished = false;

int main(int argc, char ** argv)
{
	initGL();

	glClearColor(0, 0, 0, 1);
	GL_CHECK_ERROR();
	glClearDepth(1.0f);
	GL_CHECK_ERROR();

	// Create shader
	GLuint phongProgram = createShaderProgram("Shaders/phong.vs", NULL, NULL,
			NULL, "Shaders/phong.fs");
	GLuint gradientProgram = createShaderProgram("Shaders/gradient.vs", NULL,
			NULL, NULL, "Shaders/gradient.fs");
	GLuint filterXProgram = createShaderProgram("Shaders/gauss_x.vs", NULL,
			NULL, NULL, "Shaders/gauss_x.fs");
	GLuint filterYProgram = createShaderProgram("Shaders/gauss_y.vs", NULL,
			NULL, NULL, "Shaders/gauss_y.fs");
	GLuint combineProgram = createShaderProgram("Shaders/combine.vs", NULL,
			NULL, NULL, "Shaders/combine.fs");

	// Create camera and light
	Camera camera(Vec3(0.0f, -3.0f, 3.0f), Vec3(0.0f, 1.0f, -1.0f),
			Vec3(0.0f, 0.0f, 1.0f), 6.0f);
	DirectionalLight light(Vec3(-1.0f, -1.0f, -1.0f), Vec3(1.0f, 1.0f, 1.0f));

	// Load Meshs
	Mesh sphere("Meshes/sphere.obj", phongProgram);
	Mesh stripe("Meshes/stripe.obj", gradientProgram);
	ImagePlaneMesh imageMesh(filterXProgram);
	// All postprocessing shaders specify variables in the same order, so
	// the imageMesh can be used with all of them.

	// Create two HDR framebuffers for rendering and filtering
	GLuint textures[3];
	GLuint renderbuffers[3];
	GLuint framebuffers[3];
	glGenTextures(3, textures);
	glGenRenderbuffers(3, renderbuffers);
	glGenFramebuffers(3, framebuffers);
	for (unsigned int i = 0; i < 3; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		GL_CHECK_ERROR();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 512, 512, GL_FALSE, GL_RGBA,
				GL_FLOAT, NULL);
		GL_CHECK_ERROR();

		glBindRenderbuffer(GL_RENDERBUFFER, renderbuffers[0]);
		GL_CHECK_ERROR();
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);
		GL_CHECK_ERROR();

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[i]);
		GL_CHECK_ERROR();
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textures[i],
				0);
		GL_CHECK_ERROR();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
				GL_RENDERBUFFER, renderbuffers[0]);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			exit(1);
		GL_CHECK_ERROR();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, 0);
		GL_CHECK_ERROR();
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		GL_CHECK_ERROR();
	}

	GLuint sampler;
	glGenSamplers(1, &sampler);
	GL_CHECK_ERROR();
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	GL_CHECK_ERROR();
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GL_CHECK_ERROR();
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	GL_CHECK_ERROR();
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

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

		// Render the scene to the framebuffer
		glEnable(GL_DEPTH_TEST);
		GL_CHECK_ERROR();
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[0]);
		GL_CHECK_ERROR();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GL_CHECK_ERROR();
		glUseProgram(phongProgram);
		GL_CHECK_ERROR();
		camera.ConfigureShaderProgram(phongProgram, sphere.WorldMatrix);
		light.ConfigureShaderProgram(phongProgram, camera.GetViewMatrix());
		sphere.Draw(GL_TRIANGLES);
		glUseProgram(0);
		GL_CHECK_ERROR();
		glUseProgram(gradientProgram);
		GL_CHECK_ERROR();
		camera.ConfigureShaderProgram(gradientProgram, sphere.WorldMatrix);
		light.ConfigureShaderProgram(gradientProgram, camera.GetViewMatrix());
		stripe.Draw(GL_TRIANGLES);
		glUseProgram(0);
		GL_CHECK_ERROR();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		GL_CHECK_ERROR();
		glDisable(GL_DEPTH_TEST);
		GL_CHECK_ERROR();

		// Filter in x direction
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[1]);
		GL_CHECK_ERROR();
		glUseProgram(filterXProgram);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		GL_CHECK_ERROR();
		glUniform1i(glGetUniformLocation(filterXProgram, "InputTexture"), 0);
		GL_CHECK_ERROR();
		glBindSampler(0, sampler);
		GL_CHECK_ERROR();
		imageMesh.Draw(GL_TRIANGLES);
		GL_CHECK_ERROR();
		glBindSampler(0, 0);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, 0);
		GL_CHECK_ERROR();
		glUseProgram(0);
		GL_CHECK_ERROR();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		GL_CHECK_ERROR();

		// Filter in y direction
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[2]);
		GL_CHECK_ERROR();
		glUseProgram(filterYProgram);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		GL_CHECK_ERROR();
		glUniform1i(glGetUniformLocation(filterYProgram, "InputTexture"), 0);
		GL_CHECK_ERROR();
		glBindSampler(0, sampler);
		GL_CHECK_ERROR();
		imageMesh.Draw(GL_TRIANGLES);
		GL_CHECK_ERROR();
		glBindSampler(0, 0);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, 0);
		GL_CHECK_ERROR();
		glUseProgram(0);
		GL_CHECK_ERROR();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		GL_CHECK_ERROR();

		// Combine original rendering with blurred rendering
		glUseProgram(combineProgram);
		GL_CHECK_ERROR();

		glActiveTexture(GL_TEXTURE0);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		GL_CHECK_ERROR();
		glUniform1i(glGetUniformLocation(combineProgram, "OriginalImage"), 0);
		GL_CHECK_ERROR();
		glBindSampler(0, sampler);
		GL_CHECK_ERROR();
		glActiveTexture(GL_TEXTURE1);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		GL_CHECK_ERROR();
		glUniform1i(glGetUniformLocation(combineProgram, "BlurredImage"), 1);
		GL_CHECK_ERROR();
		glBindSampler(1, sampler);
		GL_CHECK_ERROR();
		glActiveTexture(GL_TEXTURE0);
		GL_CHECK_ERROR();

		imageMesh.Draw(GL_TRIANGLES);
		GL_CHECK_ERROR();

		glBindSampler(1, 0);
		GL_CHECK_ERROR();
		glActiveTexture(GL_TEXTURE0);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, 0);
		GL_CHECK_ERROR();
		glBindSampler(0, 0);
		GL_CHECK_ERROR();
		glActiveTexture(GL_TEXTURE1);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, 0);
		GL_CHECK_ERROR();
		glActiveTexture(GL_TEXTURE0);
		GL_CHECK_ERROR();
		glUseProgram(0);
		GL_CHECK_ERROR();

		glXSwapBuffers(display, win);
		GL_CHECK_ERROR();
	}

	cout << "Exiting..." << endl;

	glDeleteSamplers(1, &sampler);
	GL_CHECK_ERROR();
	glDeleteFramebuffers(2, framebuffers);
	GL_CHECK_ERROR();
	glDeleteTextures(2, textures);
	GL_CHECK_ERROR();

	glDeleteProgram(phongProgram);
	GL_CHECK_ERROR();
	glDeleteProgram(gradientProgram);
	GL_CHECK_ERROR();
	glDeleteProgram(filterXProgram);
	GL_CHECK_ERROR();
	glDeleteProgram(filterYProgram);
	GL_CHECK_ERROR();
	glDeleteProgram(combineProgram);
	GL_CHECK_ERROR();

	exitGL();
}
