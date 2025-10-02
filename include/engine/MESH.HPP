#ifndef MESH_HPP
#define MESH_HPP

#include "glad/glad.h"

#include <vector>

#include "engine/SHADER.HPP"

class MESH
{
private:
	GLuint VAO, VBO, EBO;
	size_t indexCount;
public:
	MESH(const std::vector<GLfloat>& a_vertices, const std::vector<GLuint>& a_indices);
	~MESH();
	void Draw(const SHADER& a_shader);
};


#endif