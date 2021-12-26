#include "Utils.h"
#include "renderer.h"
#include "gamenode.h"
#include "transform.h"
#include "modules.h"

#include <iostream>


void InitializeEngine(void);
void UpdateFixed(int);
void Update(float);
void CleanUp(void);
void KeyPressed(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void RequestToCloseEngine();
void KeySpecial(int key, int x, int y);
void OnGameStart();

GameNode* rootNode;
TinyEngineRenderer* renderer;

int FIXED_UPDATE_TIMESTEP = 1000;


int main(int argc, char* argv[])
{
  renderer = new RENDERER();
  std::cout<<"Renderer created"<<std::endl;
  renderer->InitializeRenderer(argc, argv);
  std::cout<<"Renderer initialized"<<std::endl;
  InitializeEngine();
  std::cout<<"Engine initialized"<<std::endl;

  OnGameStart();
  std::cout<<"Game start"<<std::endl;
  glutMainLoop();

  printf("%s\n", "This is happening after we close the window. Thanks to the call to glutSetOption.");

  exit(EXIT_SUCCESS);
}





void InitializeEngine()
{
  //TODO should these become part of the renderer or part of different modules, like input
    glutTimerFunc(0, UpdateFixed, 0);
    glutCloseFunc(CleanUp);
    renderer->setPerFrameCallback(Update);
    glutKeyboardFunc(KeyPressed);
	  glutKeyboardUpFunc(KeyUp);
    glutSpecialFunc(KeySpecial);
}


void OnGameStart()
{

    RenderComponent* rc = new RENDER_COMPONENT();

    rootNode = GameNode::createRoot();
    Transform* transform = new Transform({0,0,0},{0,0,0},{1,1,1});
    rootNode->transform = transform;
    rootNode->renderComponent = rc;
    std::cout<<"transform "<<rootNode->transform<<std::endl;

    GameNode* newNode = new GameNode(rootNode);
    transform = new Transform({2,0,0},{0,0,0},{1,1,1});
    newNode->transform = transform;
    newNode->renderComponent = rc;

    renderer->LoadMeshes(rootNode);
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

  rootNode->transform->rotate(Vector3({deltaTime,deltaTime,deltaTime}));
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
    rootNode->children.back()->transform->position.x-=0.1;
		break;

    case GLUT_KEY_RIGHT :
		printf("Right\n");
    rootNode->children.back()->transform->position.x+=0.1;
		break;
    }
}



void RequestToCloseEngine()
{
    glutLeaveMainLoop();
}


void CleanUp()
{
    renderer->CleanUpRenderer();
    delete renderer;
    delete rootNode;
}
