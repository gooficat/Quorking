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
	glm::vec3 target;
	glm::vec3 up;
	CAMERA(SHADER* a_shader);
	void SetPerspective(float a_fov, float a_aspect, float a_near, float a_far);
	void SetOrthographic(uint16_t a_startX, uint16_t a_startY, uint16_t a_endX, uint16_t a_endY);
	~CAMERA();
	void Update(double a_deltaTime);
	void Render();
};

#endif