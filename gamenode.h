#pragma once

#include "mesh.h"
#include "transform.h"

class GameNode
{
    public:
        Transform* transform;
        Mesh* mesh;
        
        GameNode();
};
