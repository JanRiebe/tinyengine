#pragma once

#include "Utils.h"

class Vertex
{
  public:
    Vector4 Position;
    Vector4 Color;
};


class Mesh
{
  public:
    const unsigned int VERTEX_COUNT;
    const Vertex* VERTICES;
    const unsigned int INDEX_COUNT;
    const GLuint* INDICES;

    Mesh(const unsigned int vertex_count, const unsigned int index_count, const Vertex* vertices, const GLuint* indices);
};

