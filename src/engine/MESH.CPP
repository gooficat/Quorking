#include "ENGINE/MESH.HPP"

MESH::MESH(const std::vector<Vertex>& a_positions,
           GLenum a_drawMode, TEXTURE* a_texture)
{
   this->genMesh(a_positions, a_drawMode, a_texture);
}
void MESH::genMesh(const std::vector<Vertex>& a_positions,
                   GLenum a_drawMode, TEXTURE* a_texture)
{
   glGenVertexArrays(1, &(this->VAO));
   glGenBuffers(1, &(this->VBO));
   // glGenBuffers(1, &(EBO));

   glBindVertexArray(this->VAO);

   glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
   glBufferData(GL_ARRAY_BUFFER, a_positions.size() * sizeof(Vertex), &a_positions[0],
                GL_STATIC_DRAW);

   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
   // glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_faces.size() * sizeof(GLuint), &a_faces[0],
   //              GL_STATIC_DRAW);

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                         (void*)(offsetof(Vertex, Vertex::texCoord)));

   //    glEnableVertexAttribArray(0);
   //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex) * 3, (void*)0);

   // this->indexCount = a_faces.size();
   this->vertexCount = a_positions.size();
   this->drawMode = a_drawMode;
   this->texture = a_texture;
}

MESH::MESH(std::string a_path)
{
   TEXTURE* tex = nullptr;
   std::vector<Vertex> vertices;
   std::vector<glm::vec3> positions;
   std::vector<glm::vec2> texCoords;
   std::vector<glm::vec3> normals;
   std::ifstream file(a_path);
   if (file.is_open() == false)
   {
      std::cerr << "Failed to open file: " << a_path << std::endl;
      return;
   }
   std::string line;
   while (std::getline(file, line))
   {
      int vt_index = 0;
      std::string header = line.substr(0, 2);
      if (header == "v ")
      {
         positions.push_back({0, 0, 0});
         glm::vec3* v = &positions.back();
         std::sscanf(line.c_str(), "v %f %f %f", &v->x, &v->y, &v->z);
      }
      else if (header == "vt")
      {
         texCoords.push_back({0, 0});
         glm::vec2* v = &texCoords.back();
         std::sscanf(line.c_str(), "vt %f %f", &v->x, &v->y);
      }
      else if (header == "us")
      {
         normals.push_back({0, 0, 0});
         std::string texPath = line.substr(7, line.size());
         tex = new TEXTURE(texPath.c_str());
      }
      else if (header == "f ")
      {
         vertices.push_back({{0, 0, 0}, {0, 0}, {0, 0, 0}});
         Vertex* v = &vertices.back();
         uint32_t iv[3];
         uint32_t it[3];
         uint32_t in[3];
         std::sscanf(line.c_str(), "f %u/%u/%u %u/%u/%u %u/%u/%u",
            &iv[0], &it[0], &in[0],
            &iv[1], &it[1], &in[1],
            &iv[2], &it[2], &in[2]
         );
         v->position = (glm::vec3){
            positions[iv[0]],
            positions[iv[1]],
            positions[iv[2]],
         };
         v->texCoord = (glm::vec2){
            positions[iv[0]],
            positions[iv[1]],
         };
         v->normal = (glm::vec3){
            positions[iv[0]],
            positions[iv[1]],
            positions[iv[2]],
         };
      }
      else {
         std::cout << line << std::endl;
      }
   }
   // for (int f = 0; f < faces.size(); f++)
   // {
   //    std::cout << faces[f].indices << std::endl;
   // }

   this->genMesh(positions, GL_TRIANGLES, tex);
}

MESH::~MESH()
{
   glDeleteVertexArrays(1, &(this->VAO));
   glDeleteBuffers(1, &(this->VBO));
   // glDeleteBuffers(1, &(this->EBO));
   if (this->texture != nullptr)
   {
      // free(this->texture);
   }
}

void MESH::Draw(const SHADER& a_shader)
{
   this->texture->Use(a_shader);
   glBindVertexArray(this->VAO);
   // glDrawElements(drawMode, this->indexCount, GL_UNSIGNED_INT, NULL);
   glDrawArrays(drawMode, 0, this->vertexCount);
}