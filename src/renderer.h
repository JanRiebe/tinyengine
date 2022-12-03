#pragma once

#include "Utils.h"

class GameNode;

// TinyEngine Renderer interface
class TinyEngineRenderer
{
    public:
        virtual void InitializeRenderer(int, char*[]) = 0;
        virtual void LoadMeshes(GameNode* root) = 0;
        virtual void setPerFrameCallback(void (*perFrameCallback)(float)) = 0;
        virtual void CleanUpRenderer(void) = 0;
        virtual ~TinyEngineRenderer();
};


class RenderComponent
{
};


class Vertex
{
public:
    Vector4 Position;
    Vector4 Color;
};
