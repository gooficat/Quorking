#include "engine/SHADER.HPP"

GLuint createShader(GLenum a_type, const std::string& a_source) {
	GLuint shader = glCreateShader(a_type);
	const char* source = ReadFileToTxt(a_source).c_str();
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	return shader;
}

SHADER::SHADER(/* args */) {}

SHADER::~SHADER()
{
   glDeleteProgram(ID);
}

void SHADER::Compile(std::string a_vertexShaderSource, std::string a_fragmentShaderSource) {
	GLuint vertShader = createShader(GL_VERTEX_SHADER, a_vertexShaderSource);
	GLuint fragShader = createShader(GL_FRAGMENT_SHADER, a_vertexShaderSource);
	SHADER::ID = glCreateProgram();
	glAttachShader(SHADER::ID, vertShader);
	glAttachShader(SHADER::ID, fragShader);
	glLinkProgram(SHADER::ID);
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}
SHADER::~SHADER() {
	glDeleteProgram(SHADER::ID);
}
void SHADER::Use() {}
void SHADER::SetMat4(const glm::mat4& a_matrix, const char* a_name) {
	GLint location = glGetUniformLocation(SHADER::ID, a_name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &a_matrix[0][0]);
}