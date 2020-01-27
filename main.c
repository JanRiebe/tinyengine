#include "Utils.h"
#include "renderer.h"


void InitializeEngine(void);
void UpdateFixed(int);
void Update(float);
void CleanUp(void);
void KeyPressed(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void RequestToCloseEngine();
void KeySpecial(int key, int x, int y);


int FIXED_UPDATE_TIMESTEP = 1000;


int main(int argc, char* argv[])
{
    InitializeRenderer(argc, argv);
    InitializeEngine();

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
