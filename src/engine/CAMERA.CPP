#include "engine/CAMERA.HPP"

CAMERA::CAMERA(SHADER* a_shader) : shader(a_shader) {}

CAMERA::~CAMERA() {}

void CAMERA::SetPerspective(float a_fov, float a_aspect, float a_near, float a_far)
{
   CAMERA::projection = glm::perspective(glm::degrees(a_fov), a_aspect, a_near, a_far);
}
void CAMERA::SetOrthographic(uint16_t a_startX, uint16_t a_startY, uint16_t a_endX, uint16_t a_endY)
{
   CAMERA::projection = glm::ortho(a_startX, a_endX, a_startY, a_endY);
}

void CAMERA::Update(double a_deltaTime)
{
   CAMERA::view = glm::lookAt(CAMERA::transform.position, CAMERA::up, CAMERA::target);
}

void CAMERA::Render() {
	shader->Use();
	shader->SetMat4(CAMERA::view, "view");
	shader->SetMat4(CAMERA::projection, "projection");
}