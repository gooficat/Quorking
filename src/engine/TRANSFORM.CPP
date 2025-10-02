#include "ENGINE/TRANSFORM.HPP"

glm::mat4 TRANSFORM::GetMatrix()
{
   glm::mat4 matrix = glm::mat4(1.0f);
   matrix = glm::translate(matrix, TRANSFORM::position);
   matrix = glm::rotate(matrix, TRANSFORM::rotation.z, {0.0f, 0.0f, 1.0f});
   matrix = glm::rotate(matrix, TRANSFORM::rotation.y, {0.0f, 1.0f, 0.0f});
   matrix = glm::rotate(matrix, TRANSFORM::rotation.x, {1.0f, 0.0f, 0.0f});
   matrix = glm::scale(matrix, TRANSFORM::scale);
   return matrix;
}