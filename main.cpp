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
