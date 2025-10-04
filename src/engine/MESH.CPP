#include "ENGINE/MESH.HPP"


MESH::MESH(const std::vector<Vertex>& a_vertices, const std::vector<GLuint>& a_indices,
           GLenum a_drawMode, TEXTURE* a_texture)
{
   glGenVertexArrays(1, &(this->VAO));
   glGenBuffers(1, &(this->VBO));
   glGenBuffers(1, &(EBO));

   glBindVertexArray(this->VAO);

   glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
   glBufferData(GL_ARRAY_BUFFER, a_vertices.size() * sizeof(Vertex), &a_vertices[0],
                GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_indices.size() * sizeof(GLuint), &a_indices[0],
                GL_STATIC_DRAW);

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
   
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texCoord)));

//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex) * 3, (void*)0);

   this->indexCount = a_indices.size();
   this->drawMode = a_drawMode;
   this->texture = a_texture;
}

MESH::~MESH()
{
   glDeleteVertexArrays(1, &(this->VAO));
   glDeleteBuffers(1, &(this->VBO));
   glDeleteBuffers(1, &(this->EBO));
}

void MESH::Draw(const SHADER& a_shader)
{
	this->texture->Use(a_shader);
   glBindVertexArray(this->VAO);
   glDrawElements(drawMode, this->indexCount, GL_UNSIGNED_INT, NULL);
}