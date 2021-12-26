#pragma once

#include "../renderer.h"


namespace teogl
{

  class Mesh : public RenderComponent
  {
    public:
      const unsigned int VERTEX_COUNT;
      const Vertex* VERTICES;
      const unsigned int INDEX_COUNT;
      const GLuint* INDICES;
      GLuint
        ProjectionMatrixUniformLocation,
        ViewMatrixUniformLocation,
        ModelMatrixUniformLocation,
        bufferIDs[3] = { 0 },
        shaderIDs[3] = { 0 };

      Mesh(const unsigned int vertex_count, const unsigned int index_count, const Vertex* vertices, const GLuint* indices);
      ~Mesh();

      Mesh();

    private:
      void initOpenGL();
  };

}