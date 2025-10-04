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
   GLuint VAO, VBO;//, EBO;
   // size_t indexCount;
   size_t vertexCount;
   TEXTURE* texture;
   // void genMesh(const std::vector<Vertex>& a_vertices, const std::vector<GLuint>& a_faces,
   //              GLenum a_drawMode, TEXTURE* a_texture);
   void genMesh(const std::vector<Vertex>& a_vertices,
                GLenum a_drawMode, TEXTURE* a_texture);
 public:
   // MESH(const std::vector<Vertex>& a_vertices, const std::vector<GLuint>& a_faces, GLenum a_drawMode,
      //   TEXTURE* a_texture);
   MESH(const std::vector<Vertex>& a_vertices, GLenum a_drawMode, TEXTURE* a_texture);
   MESH(std::string a_path);
   ~MESH();
   virtual void Draw(const SHADER& a_shader);
   GLenum drawMode;
};

#endif