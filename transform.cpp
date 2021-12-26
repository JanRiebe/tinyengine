#include "transform.h"

Transform::Transform(Vector3 p, Vector3 r, Vector3 s):
position(p), rotation(r), scale(s)
{

}


Matrix Transform::toMatrix()
{
    Matrix m = IDENTITY_MATRIX;
    ScaleMatrix(&m, scale.x, scale.y, scale.z);
    RotateAboutX(&m, rotation.x);
    RotateAboutY(&m, rotation.y);
    RotateAboutZ(&m, rotation.z);
    TranslateMatrix(&m, position.x, position.y, position.z);
    return m;
}

void Transform::rotate(Vector3 amount)
{
    rotation.x+=amount.x;
    rotation.y+=amount.y;
    rotation.z+=amount.z;
}