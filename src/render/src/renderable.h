
#include "gltools.h"

class Mesh;
class Camera;
class DirectionalLight;

class Renderable
{
private:
    GLuint shaderProgram;
    Mesh& mesh;
public:
    Renderable(Mesh& mesh, GLuint shaderProgram);
    void Draw(Camera& camera, DirectionalLight& light);
};

//TODO give the renderable a location and use it in rendering
//Mesh already has the world position matrix, that can be utilized for this.