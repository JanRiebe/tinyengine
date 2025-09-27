#pragma once

#include <vector>

#include "transform.h"

class RenderComponent;

class GameNode
{
    public:
        Transform* transform;
        RenderComponent* renderComponent;
        std::vector<GameNode*> children;
        
        GameNode(GameNode* parent);
        static GameNode* createRoot();
        ~GameNode();
        /*
        Add a child to the game node.
        This assumes that the parent game node takes ownership of the child nodes pointer.
        */
        void addChild(GameNode* node);

    private:
        GameNode();
};
