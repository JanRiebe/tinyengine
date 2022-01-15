#include "glutInput.h"
#include <GL/freeglut.h>
#include <stdio.h>


GlutInput::GlutInput(){
    glutKeyboardFunc(KeyPressed);
    glutKeyboardUpFunc(KeyUp);
    glutSpecialFunc(KeySpecial);
}

GlutInput::~GlutInput(){
    
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