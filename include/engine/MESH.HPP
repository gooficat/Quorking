#ifndef MESH_HPP
#define MESH_HPP

#include "glad/glad.h"

#include <vector>

#include "engine/SHADER.HPP"

#include "engine/TEXTURE.HPP"

struct Vertex
{
   glm::vec3 position;
   glm::vec2 texCoord;
   glm::vec3 normal;
};

// struct Face
// {
//    GLuint indices[3];
// };

class MESH
{
 private:
   GLuint VAO, VBO;
   size_t vertexCount;
   TEXTURE* texture;
   GLenum drawMode;
   void genMesh(std::vector<Vertex> a_vertices, GLenum a_drawMode, TEXTURE* a_texture);
 public:
   MESH(std::vector<Vertex> a_vertices, GLenum a_drawMode, TEXTURE* a_texture);
   MESH(std::string a_path);
   ~MESH();
   void Draw(const SHADER& a_shader);
};

#endif