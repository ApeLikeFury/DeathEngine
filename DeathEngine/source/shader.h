#pragma once
#include <GL/glew.h>
#include <string>

class shader
{
	std::string ImportShader(std::string filepath);

	void ShaderErrorCheck(unsigned int id);

	unsigned int CompileShader(unsigned int type, const std::string& source);

	unsigned int CreateShader(std::string vertexShader, std::string fragmentShader);

	unsigned int BindShaders(std::string vertex_path, std::string fragment_path);


public:
	unsigned int shader_id;

	void use();

	shader();

	shader(std::string vertex_path, std::string fragment_path);

	void Uniform1f(const GLchar* uniform_name, float v1);

	void Uniform2f(const GLchar* uniform_name, float v1, float v2);

	void Uniform3f(const GLchar* uniform_name, float v1, float v2, float v3);

	void Uniform4f(const GLchar* uniform_name, float v1, float v2, float v3, float v4);

	void Uniform1i(const GLchar* uniform_name, int v1);

	void Uniform2i(const GLchar* uniform_name, int v1, int v2);

	void Uniform3i(const GLchar* uniform_name, int v1, int v2, int v3);

	void Uniform4i(const GLchar* uniform_name, int v1, int v2, int v3, int v4);
};
