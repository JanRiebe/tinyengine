#include "Utils.h"
#include "renderer.h"
#include "gamenode.h"
#include "transform.h"


void InitializeEngine(void);
void UpdateFixed(int);
void Update(float);
void CleanUp(void);
void KeyPressed(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void RequestToCloseEngine();
void KeySpecial(int key, int x, int y);
void OnGameStart();

const unsigned int GAME_NODE_COUNT = 2;
GameNode gameNodes[GAME_NODE_COUNT];


int FIXED_UPDATE_TIMESTEP = 1000;


int main(int argc, char* argv[])
{
    InitializeRenderer(argc, argv);
    InitializeEngine();

  OnGameStart();
  glutMainLoop();

  printf("%s\n", "This is happening after we close the window. Thanks to the call to glutSetOption.");

  exit(EXIT_SUCCESS);
}





void InitializeEngine()
{
    glutTimerFunc(0, UpdateFixed, 0);
    glutCloseFunc(CleanUp);
    setPerFrameCallback(Update);
    glutKeyboardFunc(KeyPressed);
	  glutKeyboardUpFunc(KeyUp);
    glutSpecialFunc(KeySpecial);
}


void OnGameStart()
{


        Vertex vertices[8] =
        {
          { { -.5f, -.5f,  .5f, 1 }, { 0, 0, 1, 1 } },
          { { -.5f,  .5f,  .5f, 1 }, { 1, 0, 0, 1 } },
          { {  .5f,  .5f,  .5f, 1 }, { 0, 1, 0, 1 } },
          { {  .5f, -.5f,  .5f, 1 }, { 1, 1, 0, 1 } },
          { { -.5f, -.5f, -.5f, 1 }, { 1, 1, 1, 1 } },
          { { -.5f,  .5f, -.5f, 1 }, { 1, 0, 0, 1 } },
          { {  .5f,  .5f, -.5f, 1 }, { 1, 0, 1, 1 } },
          { {  .5f, -.5f, -.5f, 1 }, { 0, 0, 1, 1 } }
        };

        GLuint indices[36] =
        {
          0,2,1,  0,3,2,
          4,3,0,  4,7,3,
          4,1,5,  4,0,1,
          3,6,2,  3,7,6,
          1,6,5,  1,2,6,
          7,5,6,  7,4,5
        };

    Mesh* mesh = new Mesh(8, 36, vertices, indices);

    gameNodes[0] = GameNode();
    gameNodes[0].mesh = mesh;
    Transform* transform = new Transform({0,0,0},{0,0,0},{1,1,1});
    gameNodes[0].transform = transform;


    gameNodes[1] = GameNode();
    gameNodes[1].mesh = mesh;
    transform = new Transform({2,0,0},{0,0,0},{1,1,1});
    gameNodes[1].transform = transform;

    InitMesh(mesh);
}



/*
    Called at fixed time step.
*/
void UpdateFixed(int Value)
{
    if (0 != Value)
    {

    }
    glutTimerFunc(FIXED_UPDATE_TIMESTEP, UpdateFixed, 1);
    //printf("%s\n","Update Fixed");
}

/*
    Called every frame.
*/
void Update(float deltaTime)
{
    //printf("%f\n", deltaTime);

    rotateCube(45.0f * ((float)(deltaTime)));
}



void KeyPressed(unsigned char key, int x, int y)
{
    switch(key)
	{

	// Escape
	case 27 :
		RequestToCloseEngine();
		break;

    default :
        printf("Pressed key: %c\nAt position: %d,%d\n", (char)key,x,y);
		break;
	}
}

void KeyUp(unsigned char key, int x, int y)
{
    printf("Lifted key: %c\nAt position: %d,%d\n", (char)key,x,y);
}

void KeySpecial(int key, int x, int y)
{
    switch(key)
	{
    case GLUT_KEY_UP :
		printf("Up\n");
		break;

    case GLUT_KEY_DOWN :
		printf("Down\n");
		break;

    case GLUT_KEY_LEFT :
		printf("Left\n");
		break;

    case GLUT_KEY_RIGHT :
		printf("Right\n");
		break;
    }
}



void RequestToCloseEngine()
{
    glutLeaveMainLoop();
}


void CleanUp()
{
    CleanUpRenderer();
}
