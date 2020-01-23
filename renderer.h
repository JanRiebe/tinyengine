#ifndef RENDERER_H
#define RENDERER_H

void InitializeRenderer(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);
void IdleFunction(void);
void CreateCube(void);
void DestroyCube(void);
void DrawCube(void);
void CleanUpRenderer(void);
void setPerFrameCallback(void (*perFrameCallback)(float));

#endif
