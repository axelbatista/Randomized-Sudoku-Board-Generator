#include "Shader.h"
#include <sstream>
#include <fstream>
#include <GL/glew.h>

Shader::Shader(const std::string& filepath) {
	std::ifstream file{ filepath };
	std::string line;
	enum class ShaderType {
		none = 0,vertex = 1, fragment = 2
	};
	std::stringstream ss[2];
	ShaderType type = ShaderType::none;
	while (std::getline(file, line)) {
		if (line.find("Vertex") != std::string::npos) {
			type = ShaderType::vertex;
		} else if(line.find("Fragment") != std::string::npos) {
			type = ShaderType::fragment;
		}
		else {
			if (type == ShaderType::vertex) {
				ss[0] << line << '\n';
			}
			else if (type == ShaderType::fragment) {
				ss[1] << line << '\n';
			}
		}
	}

	programId = glCreateProgram();
	int vs = Create(ss[0].str(), GL_VERTEX_SHADER);
	int fs = Create(ss[1].str(), GL_FRAGMENT_SHADER);

	glAttachShader(programId, vs);
	glAttachShader(programId, fs);
	glLinkProgram(programId);
	glValidateProgram(programId);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

int Shader::Create(const std::string& line, int type) {
	int shade = glCreateShader(type);
	const char* str = line.c_str();
	glShaderSource(shade, 1, &str, nullptr);
	glCompileShader(shade);
	return shade;
}

void Shader::Use() {
	glUseProgram(programId);
}

Shader::~Shader() {
	glDeleteProgram(programId);
}

void Shader::setUniform(const std::string& part, float v1, float v2, float v3, float v4) {
	glUniform4f(getUniform(part), v1, v2, v3, v4);
}

void Shader::setUniform(const std::string& part, int slot) {
	glUniform1i(getUniform(part), slot);
}

void Shader::setUniform(const std::string& part, int number, int* array)
{
	glUniform1iv(getUniform(part), number, array);
}

int Shader::getUniform(const std::string& part) {
	if (map.find(part) != map.end()) {
		return map[part];
	}
	int point = glGetUniformLocation(programId, part.c_str());
	map[part] = point;
	return point;
}