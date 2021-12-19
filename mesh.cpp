#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mesh.h"


Mesh::Mesh(const unsigned int vertex_count, const unsigned int index_count, const Vertex* vertices, const GLuint* indices):
VERTICES(vertices), VERTEX_COUNT(vertex_count), INDEX_COUNT(index_count), INDICES(indices)
{
}
