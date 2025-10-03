#include "engine/MODEL.HPP"

MODEL::MODEL(MESH* a_mesh, SHADER* a_shader) :
	mesh(a_mesh), shader(a_shader)
{
}

MODEL::~MODEL() {}

void MODEL::Render()
{
	this->shader->Use();
	glm::mat4 matrix = this->transform.GetMatrix();
	shader->SetMat4(matrix, "model");
	this->mesh->Draw(*shader);
}

void MODEL::Update(double a_deltaTime)
{

}