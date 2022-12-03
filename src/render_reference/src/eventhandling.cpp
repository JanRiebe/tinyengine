#include "Camera.h"

extern bool finished;

bool leftMouseButtonDown = false;

int lastMousePosX = 0;
int lastMousePosY = 0;

void eventHandling(Camera* camera)
{
	XEvent event;
	while (XCheckWindowEvent(display, win,
			KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask
					| PointerMotionMask, &event))
	{
		int relativeX;
		int relativeY;

		switch (event.type)
		{
		case KeyPress:
			switch (XLookupKeysym(&event.xkey, 0))
			{
			case XK_w:
				camera->MoveForward(true);
				break;
			case XK_s:
				camera->MoveBackward(true);
				break;
			case XK_a:
				camera->MoveLeft(true);
				break;
			case XK_d:
				camera->MoveRight(true);
				break;
			case XK_Escape:
				finished = true;
				break;
			}
			break;
		case KeyRelease:
			switch (XLookupKeysym(&event.xkey, 0))
			{
			case XK_w:
				camera->MoveForward(false);
				break;
			case XK_s:
				camera->MoveBackward(false);
				break;
			case XK_a:
				camera->MoveLeft(false);
				break;
			case XK_d:
				camera->MoveRight(false);
				break;
			}
			break;
		case ButtonPress:
			switch (event.xbutton.button)
			{
			case 1:
				leftMouseButtonDown = true;
				lastMousePosX = event.xbutton.x;
				lastMousePosY = event.xbutton.y;
				break;
			}
			break;
		case ButtonRelease:
			switch (event.xbutton.button)
			{
			case 1:
				leftMouseButtonDown = false;
				break;
			}
			break;
		case MotionNotify:
			relativeX = event.xmotion.x - lastMousePosX;
			relativeY = event.xmotion.y - lastMousePosY;
			lastMousePosX = event.xmotion.x;
			lastMousePosY = event.xmotion.y;
			if (leftMouseButtonDown)
			{
				camera->RotateX((float) relativeY / 500.0f);
				camera->RotateY((float) relativeX / 500.0f);
			}
			break;
		}
	}
}
