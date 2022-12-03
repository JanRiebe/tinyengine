#include "gamenode.h"
#include "renderer.h"

GameNode::GameNode(): transform(nullptr), renderComponent(nullptr)
{
}

GameNode::GameNode(GameNode* parent): transform(nullptr), renderComponent(nullptr)
{
    parent->addChild(this);
}

GameNode* GameNode::createRoot()
{
    return new GameNode();
}

GameNode::~GameNode()
{
    for(GameNode* child : children)
    {
        delete child;
    }
    delete transform;
    delete renderComponent;
}

void GameNode::addChild(GameNode* node)
{
    children.push_back(node);
}