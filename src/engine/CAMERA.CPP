#include "engine/CAMERA.HPP"

CAMERA::CAMERA(SHADER* a_shader) : shader(a_shader) {}

CAMERA::~CAMERA() {}

void CAMERA::SetPerspective(float a_fov, float a_aspect, float a_near, float a_far)
{
   CAMERA::projection = glm::perspective(glm::degrees(a_fov), a_aspect, a_near, a_far);
}
void CAMERA::SetOrthographic(uint16_t a_left, uint16_t a_right, uint16_t a_bottom, uint16_t a_top)
{
   CAMERA::projection = glm::ortho(a_left, a_right, a_bottom, a_top);
}

void CAMERA::Update(double)
{
   	CAMERA::view = glm::lookAt(CAMERA::position, CAMERA::position + CAMERA::front, CAMERA::up);
}

void CAMERA::Render() {
	shader->Use();
	shader->SetMat4(CAMERA::view, "view");
	shader->SetMat4(CAMERA::projection, "projection");
}