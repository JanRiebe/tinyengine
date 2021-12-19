#pragma once

#include "Utils.h"

class Transform
{
    public:
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;

        Transform(Vector3 p, Vector3 r, Vector3 s);
        Matrix toMatrix();

};
