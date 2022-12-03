#include <iostream>

#include "openGLrenderer.h"
#include "mesh.h"

#include "../gamenode.h"

#define WINDOW_TITLE_PREFIX "tinyEngine"


namespace teogl
{

  OpenGLRenderer* rendererSingleton = nullptr;

  OpenGLRenderer::OpenGLRenderer()
  {
    if(rendererSingleton)
      delete(rendererSingleton);
    rendererSingleton = this;
  }

  OpenGLRenderer::~OpenGLRenderer()
  {
    rendererSingleton = nullptr;
  }

  void OpenGLRenderer::setPerFrameCallback(void (*callback)(float))
  {
      perFrameCallback = callback;
  }

  void OpenGLRenderer::InitializeRenderer(int argc, char* argv[])
  {

    printf("init renderer");
    GLenum GlewInitResult;

    InitWindow(argc, argv);

    GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult) {
      fprintf(
        stderr,
        "ERROR: %s\n",
        glewGetErrorString(GlewInitResult)
      );
      exit(EXIT_FAILURE);
    }

    fprintf(
      stdout,
      "INFO: OpenGL Version: %s\n",
      glGetString(GL_VERSION)
    );

      glGetError();

      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

      glEnable(GL_DEPTH_TEST);
      // Defining how the depth shall be tested.
      // GL_LESS means we show a fragment, if it is closer to the camera.
      glDepthFunc(GL_LESS);
      ExitOnGLError("ERROR: Could not set OpenGL depth testing options");

      glEnable(GL_CULL_FACE);
      glCullFace(GL_BACK);
      glFrontFace(GL_CCW);
      ExitOnGLError("ERROR: Could not set OpenGL culling options");

      ModelMatrix = IDENTITY_MATRIX;
      ProjectionMatrix = IDENTITY_MATRIX;
      ViewMatrix = IDENTITY_MATRIX;
      TranslateMatrix(&ViewMatrix, 0, 0, -2);
  }

  void OpenGLRenderer::LoadMeshes(GameNode* root)
  {
    //TODO load all the meshes in the children
    //Actually I will want to go through all game nodes and see whether
    //they have render components attached and then load those.
    //InitMesh(root->mesh);
    gameNodesRoot = root;
  }

  void OpenGLRenderer::InitWindow(int argc, char* argv[])
  {
    printf("init window");
    glutInit(&argc, argv);

    glutInitContextVersion(4, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
      GLUT_ACTION_ON_WINDOW_CLOSE,
      GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

    glutInitWindowSize(CurrentWidth, CurrentHeight);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

    if(WindowHandle < 1) {
      fprintf(
        stderr,
        "ERROR: Could not create a new rendering window.\n"
      );
      exit(EXIT_FAILURE);
    }

      glutReshapeFunc(ResizeFunction);
      glutDisplayFunc(RenderFunction);
      glutIdleFunc(IdleFunction);
  }

  void ResizeFunction(int Width, int Height)
  {
    printf("resize a");
    rendererSingleton->CurrentWidth = Width;
    rendererSingleton->CurrentHeight = Height;
    glViewport(0, 0, rendererSingleton->CurrentWidth, rendererSingleton->CurrentHeight);
    rendererSingleton->ProjectionMatrix =
    CreateProjectionMatrix(
      60,
      (float)rendererSingleton->CurrentWidth / rendererSingleton->CurrentHeight,
      1.0f,
      100.0f
    );

    //TODO if root has no renderComponent use a default shader
    glUseProgram(((Mesh*)(rendererSingleton->gameNodesRoot->renderComponent))->shaderIDs[0]);
    glUniformMatrix4fv(((Mesh*)rendererSingleton->gameNodesRoot->renderComponent)->ProjectionMatrixUniformLocation, 1, GL_FALSE, rendererSingleton->ProjectionMatrix.m);
    glUseProgram(0);

    printf("width %d ", rendererSingleton->CurrentWidth);
    printf("height %d\n", rendererSingleton->CurrentHeight);
  }

  float OpenGLRenderer::calculateDeltaTime()
  {
      static float lastTime;
      float now = glutGet(GLUT_ELAPSED_TIME);
      float deltaTime = now - lastTime;
      lastTime = now;
      return ((float)deltaTime)/1000;
  }

  void RenderFunction(void)
  {
    std::cout<<"render"<<std::endl;
    ++rendererSingleton->frameCount;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    rendererSingleton->drawGameTree(rendererSingleton->gameNodesRoot);

    glutSwapBuffers();
    glutPostRedisplay();

    if(rendererSingleton->perFrameCallback != NULL)
      rendererSingleton->perFrameCallback(rendererSingleton->calculateDeltaTime());
  }

  void OpenGLRenderer::drawGameTree(GameNode* root)
  {
    printf("draw game tree\n");
    if(root->renderComponent != nullptr)
      DrawMesh((Mesh*)root->renderComponent, root->transform);
    for(GameNode* child : root->children)
    {
      drawGameTree(child);
    }
  }



  void IdleFunction(void)
  {
    glutPostRedisplay();
  }


/*

  void OpenGLRenderer::rotateCube(float rotation)
  {
    printf("rotate cube");
      CubeRotation += rotation;
      //printf("%f\n", CubeRotation);
  }

*/

  void OpenGLRenderer::DrawMesh(Mesh* mesh, Transform* transform)
  {
    printf("draw mesh\n");
      ModelMatrix = transform->toMatrix();

      glUseProgram(mesh->shaderIDs[0]);
      ExitOnGLError("ERROR: Could not use the shader program");

      // Loading the matrices into the shader.
      // The 1 here is the number of matrices >1 for an array of matrices.
      // The GL_FALSE here is for whether the matrix should be transposed.
      glUniformMatrix4fv(mesh->ModelMatrixUniformLocation, 1, GL_FALSE, ModelMatrix.m);
      glUniformMatrix4fv(mesh->ViewMatrixUniformLocation, 1, GL_FALSE, ViewMatrix.m);
      ExitOnGLError("ERROR: Could not set the shader uniforms");

      glBindVertexArray(mesh->bufferIDs[0]);//BufferIds[0]);
      ExitOnGLError("ERROR: Could not bind the VAO for drawing purposes");

      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);
      ExitOnGLError("ERROR: Could not draw the mesh");

      glBindVertexArray(0);
      glUseProgram(0);
  }



  void OpenGLRenderer::CleanUpRenderer()
  {

    printf("clean up");
      //DestroyMesh();
  }
}