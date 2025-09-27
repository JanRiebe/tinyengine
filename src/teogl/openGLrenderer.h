#pragma once

#include "../renderer.h"

class Transform;
class Matrix;
class GameNode;

namespace teogl
{

    class Mesh;

    void ResizeFunction(int, int);
    void RenderFunction(void);
    void IdleFunction(void);

    class OpenGLRenderer: public TinyEngineRenderer
    {
        public:
            OpenGLRenderer();
            ~OpenGLRenderer();

            void InitializeRenderer(int, char*[]);
            void setPerFrameCallback(void (*perFrameCallback)(float));
            void LoadMeshes(GameNode* root);
            void CleanUpRenderer(void);
            
            friend void ResizeFunction(int, int);
            friend void RenderFunction(void);
            friend void IdleFunction(void);

        private:
            void InitWindow(int, char*[]);
            void DestroyMesh(Mesh* mesh);
            void DrawMesh(Mesh* mesh, Transform* transform);
            void rotateCube(float);
            float calculateDeltaTime();
            void drawGameTree(GameNode* root);


            int
                CurrentWidth = 800,
                CurrentHeight = 600,
                WindowHandle = 0;

            Matrix
                ProjectionMatrix,
                ViewMatrix,
                ModelMatrix;

                float CubeRotation = 0;
                clock_t LastTime = 0;

            GameNode*
                gameNodesRoot;


            unsigned frameCount = 0;

            void (*perFrameCallback)(float) = NULL;
    };
}