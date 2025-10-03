#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

#include "NODE.HPP"
#include "SHADER.HPP"

class CAMERA : public NODE
{
private:
	glm::mat4 view, projection;
	SHADER* shader;
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	bool targetMode;
	CAMERA(SHADER* a_shader);
	void SetPerspective(float a_fov, float a_aspect, float a_near, float a_far);
	void SetOrthographic(uint16_t a_left, uint16_t a_right, uint16_t a_bottom, uint16_t a_top);
	~CAMERA();
	void Update(double a_deltaTime);
	void Render();
};

#endif