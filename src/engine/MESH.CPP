#include "ENGINE/MESH.HPP"

MESH::MESH(const std::vector<GLfloat>& a_vertices, const std::vector<GLuint>& a_indices,
           GLenum a_drawMode)
{
   glGenVertexArrays(1, &(MESH::VAO));
   glGenBuffers(1, &(MESH::VBO));
   glGenBuffers(1, &(EBO));

   glBindVertexArray(MESH::VAO);

   glBindBuffer(GL_ARRAY_BUFFER, MESH::VBO);
   glBufferData(GL_ARRAY_BUFFER, a_vertices.size() * sizeof(GLfloat), &a_vertices[0],
                GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MESH::EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_indices.size() * sizeof(GLuint), &a_indices[0],
                GL_STATIC_DRAW);

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (void*)0);

   glBindVertexArray(0);
   MESH::indexCount = a_indices.size();
   MESH::drawMode = a_drawMode;
}

MESH::~MESH()
{
   glDeleteVertexArrays(1, &(MESH::VAO));
   glDeleteBuffers(1, &(MESH::VBO));
   glDeleteBuffers(1, &(MESH::EBO));
}

void MESH::Draw(const SHADER& a_shader)
{
   glBindVertexArray(MESH::VAO);
   glDrawElements(MESH::drawMode, MESH::indexCount, GL_UNSIGNED_INT, NULL);
}
