#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct TRANSFORM
{
   glm::vec3 position;
   glm::vec3 rotation;
	glm::vec3 scale;

	void Translate(glm::vec3 a_translation);
	void Rotate(glm::vec3 a_rotation);
	void RotateX(float a_angle);
	void RotateY(float a_angle);
	void RotateZ(float a_angle);
	glm::mat4 GetMatrix();
};

#endif