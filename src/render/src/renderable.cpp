
#include "renderable.h"

#include "Camera.h"
#include "DirectionalLight.h"
#include "Mesh.h"


Renderable::Renderable(Mesh& mesh, GLuint shaderProgram):mesh(mesh), shaderProgram(shaderProgram){}

void Renderable::Draw(Camera& camera, DirectionalLight& light)
{
    glUseProgram(shaderProgram);
    camera.ConfigureShaderProgram(shaderProgram, mesh.WorldMatrix);
    light.ConfigureShaderProgram(shaderProgram, camera.GetViewMatrix());
    mesh.Draw(GL_TRIANGLES);
}