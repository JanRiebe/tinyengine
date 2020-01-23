#include "Utils.h"
#include "renderer.h"


void InitializeEngine(void);
void UpdateFixed(int);
void Update(float);
void CleanUp(void);

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
    printf("%s\n","Update Fixed");
}

/*
    Called every frame.
*/
void Update(float deltaTime)
{
    printf("%f\n", deltaTime);
}



void CleanUp()
{
    CleanUpRenderer();
}
