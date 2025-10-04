#ifndef MESH_HPP
#define MESH_HPP

#include "glad/glad.h"

#include <vector>

#include "engine/SHADER.HPP"

#include "engine/TEXTURE.HPP"

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class MESH
{
private:
	GLuint VAO, VBO, EBO;
	size_t indexCount;
	TEXTURE* texture;
public:
	MESH(const std::vector<Vertex>& a_vertices, const std::vector<GLuint>& a_indices, GLenum a_drawMode, TEXTURE* a_texture);
	~MESH();
	virtual void Draw(const SHADER& a_shader);
	GLenum drawMode;
};

#endif