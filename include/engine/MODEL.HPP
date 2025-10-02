#ifndef MODEL_HPP
#define MODEL_HPP

#include "engine/MESH.HPP"
#include "engine/NODE.HPP"
#include "engine/SHADER.HPP"

class MODEL : public NODE
{
 private:
   MESH* mesh;

 public:
   SHADER* shader;
   MODEL(MESH* a_mesh, SHADER* a_shader);
   void Update(double a_deltaTime);
   void Render();
   ~MODEL();
};

#endif