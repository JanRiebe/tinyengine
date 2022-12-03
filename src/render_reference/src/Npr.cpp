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

	glClearColor(1, 1, 1, 1);
	GL_CHECK_ERROR();
	glClearDepth(1.0f);
	GL_CHECK_ERROR();
	glEnable(GL_DEPTH_TEST);
	GL_CHECK_ERROR();

	// Create shader
	GLuint shaderProgram = createShaderProgram("Shaders/npr.vs", NULL, NULL,
			NULL, "Shaders/npr.fs");

	// Create camera and light
	Camera camera(Vec3(0.0f, -3.0f, 3.0f), Vec3(0.0f, 1.0f, -1.0f),
			Vec3(0.0f, 0.0f, 1.0f), 6.0f);
	DirectionalLight light(Vec3(-1.0f, -1.0f, -1.0f), Vec3(1.0f, 1.0f, 1.0f));

	// Load Mesh
	Mesh mesh("Meshes/sphere.obj", shaderProgram);

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

		camera.ConfigureShaderProgram(shaderProgram, mesh.WorldMatrix);
		light.ConfigureShaderProgram(shaderProgram, camera.GetViewMatrix());
		mesh.Draw(GL_TRIANGLES);

		glUseProgram(0);
		GL_CHECK_ERROR();
		glXSwapBuffers(display, win);
		GL_CHECK_ERROR();
	}

	cout << "Exiting..." << endl;

	exitGL();
}
