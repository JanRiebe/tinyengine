#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mesh.h"

#include "../renderer.h"

namespace teogl
{

    Mesh::Mesh::Mesh(): VERTEX_COUNT(8), INDEX_COUNT(36)
    {


        Vertex vertices[8] =
        {
          { { -.5f, -.5f,  .5f, 1 }, { 0, 0, 1, 1 } },
          { { -.5f,  .5f,  .5f, 1 }, { 1, 0, 0, 1 } },
          { {  .5f,  .5f,  .5f, 1 }, { 0, 1, 0, 1 } },
          { {  .5f, -.5f,  .5f, 1 }, { 1, 1, 0, 1 } },
          { { -.5f, -.5f, -.5f, 1 }, { 1, 1, 1, 1 } },
          { { -.5f,  .5f, -.5f, 1 }, { 1, 0, 0, 1 } },
          { {  .5f,  .5f, -.5f, 1 }, { 1, 0, 1, 1 } },
          { {  .5f, -.5f, -.5f, 1 }, { 0, 0, 1, 1 } }
        };

        GLuint indices[36] =
        {
          0,2,1,  0,3,2,
          4,3,0,  4,7,3,
          4,1,5,  4,0,1,
          3,6,2,  3,7,6,
          1,6,5,  1,2,6,
          7,5,6,  7,4,5
        };

        VERTICES = vertices;
        INDICES = indices;

        initOpenGL();
    }


    Mesh::Mesh(const unsigned int vertex_count, const unsigned int index_count, const Vertex* vertices, const GLuint* indices):
    VERTICES(vertices), VERTEX_COUNT(vertex_count), INDEX_COUNT(index_count), INDICES(indices)
    {
        initOpenGL();
    }

    Mesh::~Mesh()
    {
        glDetachShader(shaderIDs[0], shaderIDs[1]);
        glDetachShader(shaderIDs[0], shaderIDs[2]);
        glDeleteShader(shaderIDs[1]);
        glDeleteShader(shaderIDs[2]);
        glDeleteProgram(shaderIDs[0]);
        ExitOnGLError("ERROR: Could not destroy the shaders");

        glDeleteBuffers(2, &bufferIDs[1]);// &BufferIds[1]);
        glDeleteVertexArrays(1, &bufferIDs[0]);// &BufferIds[0]);
        ExitOnGLError("ERROR: Could not destroy the buffer objects");
    }
    
    void Mesh::initOpenGL()
    {

        shaderIDs[0] = glCreateProgram();
        ExitOnGLError("ERROR: Could not create the shader program");

        shaderIDs[1] = LoadShader("../src/shader/SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);
        shaderIDs[2] = LoadShader("../src/shader/SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
        glAttachShader(shaderIDs[0], shaderIDs[1]);
        glAttachShader(shaderIDs[0], shaderIDs[2]);

        glLinkProgram(shaderIDs[0]);
        ExitOnGLError("ERROR: Could not link the shader program");

        // Retrieving the locations (like pointers) to the variables in the shader that we can then loading the matrices into.
        ModelMatrixUniformLocation = glGetUniformLocation(shaderIDs[0], "ModelMatrix");
        ViewMatrixUniformLocation = glGetUniformLocation(shaderIDs[0], "ViewMatrix");
        ProjectionMatrixUniformLocation = glGetUniformLocation(shaderIDs[0], "ProjectionMatrix");
        ExitOnGLError("ERROR: Could not get the shader uniform locations");

        glGenBuffers(2, &bufferIDs[1]);// &BufferIds[1]);
        ExitOnGLError("ERROR: Could not generate the buffer objects");

        glGenVertexArrays(1, &(bufferIDs[0]));// &BufferIds[0]);
        ExitOnGLError("ERROR: Could not generate the VAO");
        glBindVertexArray(bufferIDs[0]);//BufferIds[0]);
        ExitOnGLError("ERROR: Could not bind the VAO");

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        ExitOnGLError("ERROR: Could not enable vertex attributes");

        glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[1]);// BufferIds[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*VERTEX_COUNT, VERTICES, GL_STATIC_DRAW);
        ExitOnGLError("ERROR: Could not bind the VBO to the VAO");

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vector4));
        ExitOnGLError("ERROR: Could not set VAO attributes");

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIDs[2]);// BufferIds[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES[0])*INDEX_COUNT, INDICES, GL_STATIC_DRAW);
        ExitOnGLError("ERROR: Could not bind the IBO to the VAO");

        glBindVertexArray(0);
    }
}