#include "engine/MODEL.HPP"

MODEL::MODEL(MESH* a_mesh, SHADER* a_shader) :
	mesh(a_mesh), shader(a_shader)
{
}

MODEL::~MODEL() {}

void MODEL::Render()
{
	MODEL::shader->Use();
	glm::mat4 matrix = MODEL::transform.GetMatrix();
	shader->SetMat4(matrix, "model");
	MODEL::mesh->Draw(*shader);
}

void MODEL::Update(double a_deltaTime)
{

}