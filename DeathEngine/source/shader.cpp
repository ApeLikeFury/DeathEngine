#include <GL/glew.h>
#include <fstream>
#include <string>
#include "errors.h"
#include "shader.h"

std::string shader::ImportShader(std::string filepath)
{
	std::string shader;
	std::fstream myFile;
	myFile.open(filepath, std::ios::in);
	if (myFile.is_open())
	{
		std::string line;
		while (getline(myFile, line))
		{
			shader += line + "\n";
		}
	}
	return shader;
}

void shader::ShaderErrorCheck(unsigned int id)
{
	int result;
	Error(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		Error(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = new char[sizeof(char) * length];
		Error(glGetShaderInfoLog(id, length, &length, message));
		cout << "Failed to compile" << endl;
		cout << message << endl;
		Error(glDeleteShader(id));
		return;
	}
}

unsigned int shader::CompileShader(unsigned int type, const std::string& source)
{
	Error(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	Error(glShaderSource(id, 1, &src, nullptr));
	Error(glCompileShader(id));

	ShaderErrorCheck(id);

	return id;
}

unsigned int shader::CreateShader(std::string vertexShader, std::string fragmentShader)
{
	Error(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	Error(glAttachShader(program, vs));
	Error(glAttachShader(program, fs));
	Error(glLinkProgram(program));
	Error(glValidateProgram(program));

	Error(glDeleteShader(vs));
	Error(glDeleteShader(fs));

	return program;
}

unsigned int shader::BindShaders(std::string vertex_path, std::string fragment_path)
{
	std::string fragmentShader = ImportShader(fragment_path);
	std::string vertexShader = ImportShader(vertex_path);

	return CreateShader(vertexShader, fragmentShader);
}

void shader::use()
{
	glUseProgram(shader_id);
}

shader::shader()
{
}

shader::shader(std::string vertex_path, std::string fragment_path)
{
	shader_id = BindShaders(vertex_path, fragment_path);
}

void shader::Uniform1f(const GLchar* uniform_name, float v1)
{

	unsigned int location = glGetUniformLocation(shader_id, uniform_name);
	glUniform1f(location, v1);
}

void shader::Uniform2f(const GLchar* uniform_name, float v1, float v2)
{
	unsigned int location = glGetUniformLocation(shader_id, uniform_name);
	glUniform2f(location, v1, v2);
}

void shader::Uniform3f(const GLchar* uniform_name, float v1, float v2, float v3)
{
	unsigned int location = glGetUniformLocation(shader_id, uniform_name);
	glUniform3f(location, v1, v2, v3);
}

void shader::Uniform4f(const GLchar* uniform_name, float v1, float v2, float v3, float v4)
{
	unsigned int location = glGetUniformLocation(shader_id, uniform_name);
	glUniform4f(location, v1, v2, v3, v4);
}

void shader::Uniform1i(const GLchar* uniform_name, int v1)
{

	unsigned int location = glGetUniformLocation(shader_id, uniform_name);
	glUniform1i(location, v1);
}

void shader::Uniform2i(const GLchar* uniform_name, int v1, int v2)
{
	unsigned int location = glGetUniformLocation(shader_id, uniform_name);
	glUniform2i(location, v1, v2);
}

void shader::Uniform3i(const GLchar* uniform_name, int v1, int v2, int v3)
{
	unsigned int location = glGetUniformLocation(shader_id, uniform_name);
	glUniform3i(location, v1, v2, v3);
}

void shader::Uniform4i(const GLchar* uniform_name, int v1, int v2, int v3, int v4)
{
	unsigned int location = glGetUniformLocation(shader_id, uniform_name);
	glUniform4i(location, v1, v2, v3, v4);
}
