#include "Camera.h"
#include "DirectionalLight.h"
#include "Mesh.h"
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
	glEnable(GL_DEPTH_TEST);
	GL_CHECK_ERROR();

	// Create shader
	GLuint genShadowMapProgram = createShaderProgram("Shaders/genShadowMap.vs",
			NULL, NULL, NULL, "Shaders/genShadowMap.fs");

	GLuint shaderProgram = createShaderProgram("Shaders/renderShadowMap.vs",
			NULL, NULL, NULL, "Shaders/renderShadowMap.fs");

	// Create camera and light
	Camera camera(Vec3(0.0f, -3.0f, 3.0f), Vec3(0.0f, 1.0f, -1.0f),
			Vec3(0.0f, 0.0f, 1.0f), 6.0f);
	DirectionalLight light(Vec3(-1.0f, -1.0f, -1.0f), Vec3(1.0f, 1.0f, 1.0f));

	// Load Mesh
	Mesh mesh("Meshes/scene.obj", shaderProgram);

	// Create the shadow map
	GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	GL_CHECK_ERROR();
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	GL_CHECK_ERROR();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, 1024, 1024, GL_FALSE,
			GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	GL_CHECK_ERROR();

	GLuint depthFramebuffer;
	glGenFramebuffers(1, &depthFramebuffer);
	GL_CHECK_ERROR();
	glBindFramebuffer(GL_FRAMEBUFFER, depthFramebuffer);
	GL_CHECK_ERROR();
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);
	GL_CHECK_ERROR();
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		exit(1);
	GL_CHECK_ERROR();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	GL_CHECK_ERROR();
	glBindTexture(GL_TEXTURE_2D, 0);
	GL_CHECK_ERROR();
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	GL_CHECK_ERROR();

	GLuint samplerDepth;
	glGenSamplers(1, &samplerDepth);
	GL_CHECK_ERROR();
	glSamplerParameteri(samplerDepth, GL_TEXTURE_WRAP_S, GL_REPEAT);
	GL_CHECK_ERROR();
	glSamplerParameteri(samplerDepth, GL_TEXTURE_WRAP_T, GL_REPEAT);
	GL_CHECK_ERROR();
	glSamplerParameteri(samplerDepth, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GL_CHECK_ERROR();
	glSamplerParameteri(samplerDepth, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameteri(samplerDepth, GL_TEXTURE_COMPARE_MODE,
			GL_COMPARE_REF_TO_TEXTURE);
	glSamplerParameteri(samplerDepth, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
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

		// Render the shadow map
		glBindFramebuffer(GL_FRAMEBUFFER, depthFramebuffer);
		GL_CHECK_ERROR();
		glViewport(0, 0, 1024, 1024);
		GL_CHECK_ERROR();
		glClear(GL_DEPTH_BUFFER_BIT);
		GL_CHECK_ERROR();
		glUseProgram(genShadowMapProgram);
		GL_CHECK_ERROR();
		Matrix4x4 modelLightMatrix = Matrix4x4::ViewMatrix(-light.Direction * 5,
				light.Direction, Vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(
				glGetUniformLocation(genShadowMapProgram, "ModelLightMatrix"),
				1, GL_TRUE, &modelLightMatrix._00);
		mesh.Draw(GL_TRIANGLES);
		glUseProgram(0);
		GL_CHECK_ERROR();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		GL_CHECK_ERROR();
		glViewport(0, 0, 512, 512);
		GL_CHECK_ERROR();

		// Render the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GL_CHECK_ERROR();
		glUseProgram(shaderProgram);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		GL_CHECK_ERROR();
		glGenerateMipmap(GL_TEXTURE_2D);
		GL_CHECK_ERROR();
		glBindSampler(0, samplerDepth);
		GL_CHECK_ERROR();
		glUniform1i(glGetUniformLocation(shaderProgram, "ShadowMap"), 0);
		GL_CHECK_ERROR();
		camera.ConfigureShaderProgram(shaderProgram, mesh.WorldMatrix);
		light.ConfigureShaderProgram(shaderProgram, camera.GetViewMatrix());
		glUniformMatrix4fv(
				glGetUniformLocation(shaderProgram, "ModelLightMatrix"), 1,
				GL_TRUE, &modelLightMatrix._00);
		mesh.Draw(GL_TRIANGLES);
		glBindSampler(0, 0);
		GL_CHECK_ERROR();
		glBindTexture(GL_TEXTURE_2D, 0);
		GL_CHECK_ERROR();
		glUseProgram(0);
		GL_CHECK_ERROR();
		glXSwapBuffers(display, win);
		GL_CHECK_ERROR();
	}

	cout << "Exiting..." << endl;

	GL_CHECK_ERROR();
	glDeleteSamplers(1, &samplerDepth);
	GL_CHECK_ERROR();
	glDeleteFramebuffers(1, &depthFramebuffer);
	GL_CHECK_ERROR();
	glDeleteTextures(1, &depthTexture);

	exitGL();
}
