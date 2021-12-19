#pragma once

class Mesh;
class Transform;

void InitializeRenderer(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);
void IdleFunction(void);
void InitMesh(Mesh*);
void DestroyMesh(void);
void DrawMesh(Transform*);
void CleanUpRenderer(void);
void setPerFrameCallback(void (*perFrameCallback)(float));
void rotateCube(float);
