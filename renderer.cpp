#include "renderer.h"
#include "Utils.h"
#include "mesh.h"
#include "gamenode.h"

#define WINDOW_TITLE_PREFIX "tinyEngine"

int
  CurrentWidth = 800,
  CurrentHeight = 600,
  WindowHandle = 0;


GLuint
    ProjectionMatrixUniformLocation,
    ViewMatrixUniformLocation,
    ModelMatrixUniformLocation,
    BufferIds[3] = { 0 },
    ShaderIds[3] = { 0 };

Matrix
    ProjectionMatrix,
    ViewMatrix,
    ModelMatrix;

    float CubeRotation = 0;
    clock_t LastTime = 0;


unsigned frameCount = 0;

void (*perFrameCallback)(float) = NULL;

void setPerFrameCallback(void (*callback)(float))
{
    perFrameCallback = callback;
}

void InitializeRenderer(int argc, char* argv[])
{

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

void InitWindow(int argc, char* argv[])
{
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
    /*
    void InitMesh(void);
    void DestroyMesh(void);
    void DrawMesh(void);
    */
}

void ResizeFunction(int Width, int Height)
{
  CurrentWidth = Width;
  CurrentHeight = Height;
  glViewport(0, 0, CurrentWidth, CurrentHeight);
  ProjectionMatrix =
  CreateProjectionMatrix(
    60,
    (float)CurrentWidth / CurrentHeight,
    1.0f,
    100.0f
  );

    glUseProgram(ShaderIds[0]);
    glUniformMatrix4fv(ProjectionMatrixUniformLocation, 1, GL_FALSE, ProjectionMatrix.m);
    glUseProgram(0);

  printf("width %d ", CurrentWidth);
  printf("height %d\n", CurrentHeight);
}

float calculateDeltaTime()
{
    static float lastTime;
    float now = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = now - lastTime;
    lastTime = now;
    return ((float)deltaTime)/1000;
}

void RenderFunction(void)
{
  ++frameCount;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  DrawMesh(new Transform({0,0,0},{0,0,0},{0,0,0}));

  glutSwapBuffers();
  glutPostRedisplay();

  if(perFrameCallback != NULL)
    perFrameCallback(calculateDeltaTime());
}



void IdleFunction(void)
{
  glutPostRedisplay();
}




void InitMesh(Mesh* mesh)
{

    ShaderIds[0] = glCreateProgram();
    ExitOnGLError("ERROR: Could not create the shader program");

    ShaderIds[1] = LoadShader("../src/shader/SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);
    ShaderIds[2] = LoadShader("../src/shader/SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
    glAttachShader(ShaderIds[0], ShaderIds[1]);
    glAttachShader(ShaderIds[0], ShaderIds[2]);

    glLinkProgram(ShaderIds[0]);
    ExitOnGLError("ERROR: Could not link the shader program");

    // Retrieving the locations (like pointers) to the variables in the shader that we can then loading the matrices into.
    ModelMatrixUniformLocation = glGetUniformLocation(ShaderIds[0], "ModelMatrix");
    ViewMatrixUniformLocation = glGetUniformLocation(ShaderIds[0], "ViewMatrix");
    ProjectionMatrixUniformLocation = glGetUniformLocation(ShaderIds[0], "ProjectionMatrix");
    ExitOnGLError("ERROR: Could not get the shader uniform locations");

    glGenBuffers(2, &BufferIds[1]);
    ExitOnGLError("ERROR: Could not generate the buffer objects");

    glGenVertexArrays(1, &BufferIds[0]);
    ExitOnGLError("ERROR: Could not generate the VAO");
    glBindVertexArray(BufferIds[0]);
    ExitOnGLError("ERROR: Could not bind the VAO");

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    ExitOnGLError("ERROR: Could not enable vertex attributes");

    glBindBuffer(GL_ARRAY_BUFFER, BufferIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*mesh->VERTEX_COUNT, mesh->VERTICES, GL_STATIC_DRAW);
    ExitOnGLError("ERROR: Could not bind the VBO to the VAO");

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vector4));
    ExitOnGLError("ERROR: Could not set VAO attributes");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferIds[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh->INDICES[0])*mesh->INDEX_COUNT, mesh->INDICES, GL_STATIC_DRAW);
    ExitOnGLError("ERROR: Could not bind the IBO to the VAO");

    glBindVertexArray(0);
}


//TODO this destroys the mesh on the graphics card but not the mesh object that was used to create it.
// How do I want to handle the creating and destruction of these? Perhaps in the mesh module, meshes should be managed.
// The renderer only uses them, reading data from them.
void DestroyMesh(void)
{
  glDetachShader(ShaderIds[0], ShaderIds[1]);
  glDetachShader(ShaderIds[0], ShaderIds[2]);
  glDeleteShader(ShaderIds[1]);
  glDeleteShader(ShaderIds[2]);
  glDeleteProgram(ShaderIds[0]);
  ExitOnGLError("ERROR: Could not destroy the shaders");

  glDeleteBuffers(2, &BufferIds[1]);
  glDeleteVertexArrays(1, &BufferIds[0]);
  ExitOnGLError("ERROR: Could not destroy the buffer objects");
}


void rotateCube(float rotation)
{
    CubeRotation += rotation;
    //printf("%f\n", CubeRotation);
}


void DrawMesh(Transform* transform)
{
    ModelMatrix = transform->toMatrix();

    glUseProgram(ShaderIds[0]);
    ExitOnGLError("ERROR: Could not use the shader program");

    // Loading the matrices into the shader.
    // The 1 here is the number of matrices >1 for an array of matrices.
    // The GL_FALSE here is for whether the matrix should be transposed.
    glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, ModelMatrix.m);
    glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, ViewMatrix.m);
    ExitOnGLError("ERROR: Could not set the shader uniforms");

    glBindVertexArray(BufferIds[0]);
    ExitOnGLError("ERROR: Could not bind the VAO for drawing purposes");

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);
    ExitOnGLError("ERROR: Could not draw the mesh");

    glBindVertexArray(0);
    glUseProgram(0);
}



void CleanUpRenderer()
{
    DestroyMesh();
}
