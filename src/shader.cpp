#include "shader.hpp"

#include <iostream>

#include <glad/glad.h>

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main() {
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 430 core
out vec4 FragColor;

layout (location = 20) uniform vec4 uColor;

void main() {
	FragColor = uColor;
}
)";

const char* fragmentShaderSourceOrange = R"(
#version 330 core
out vec4 FragColor;

void main() {
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

const char* fragmentShaderSourceYellow = R"(
#version 330 core
out vec4 FragColor;

void main() {
	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}
)";

static bool error_in_shader_program_compilation = false;

bool isError() {
	return error_in_shader_program_compilation;
}

enum class QueryType {
	VERTEX,
	FRAGMENT,
	PROGRAM
};

using statusQuery_t = void (*) (GLuint, GLenum, GLint*);
using infoLog_t = void (*) (GLuint, GLsizei, GLsizei*, GLchar*);

static const char* errorMessage(QueryType qt) {
	switch (qt) {
	case QueryType::VERTEX: return "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
	case QueryType::FRAGMENT: return "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
	case QueryType::PROGRAM: return "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
	}
	return "ERROR::UNKNOWN\n";
}

/* For both (shader) compile and (program) link */
static void statusCheck(statusQuery_t statusQuery, infoLog_t getInfoLog, GLuint object, GLenum en, QueryType qt) {
	GLint success;
	char infoLog[512];

	statusQuery(object, en, &success);
	if (!success) {
		getInfoLog(object, 512, nullptr, infoLog);
		std::cerr << errorMessage(qt) << infoLog;
		
		error_in_shader_program_compilation = true;
	}
}

/* Create shader, set source and compile. And invoke statusCheck */
static GLuint createShader(GLenum shaderType, const char *shaderSource, QueryType qt) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	statusCheck(glGetShaderiv, glGetShaderInfoLog, shader, GL_COMPILE_STATUS, qt);

	return shader;
}

static GLuint createProgram(GLuint vertexShader, GLuint fragmentShader) {
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	statusCheck(glGetProgramiv, glGetProgramInfoLog, shaderProgram, GL_LINK_STATUS, QueryType::PROGRAM);

	// No longer need shader objects after program linked
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	return shaderProgram;
}

std::pair<GLuint, GLuint> createShaderPrograms() {
	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource, QueryType::VERTEX);
	GLuint fragmentShaderOrange = createShader(GL_FRAGMENT_SHADER, fragmentShaderSourceOrange, QueryType::FRAGMENT);
	GLuint fragmentShaderYellow = createShader(GL_FRAGMENT_SHADER, fragmentShaderSourceYellow, QueryType::FRAGMENT);

	// shader program
	GLuint shaderProgramOrange = createProgram(vertexShader, fragmentShaderOrange);
	GLuint shaderProgramYellow = createProgram(vertexShader, fragmentShaderYellow);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderOrange);
	glDeleteShader(fragmentShaderYellow);

	return std::pair{shaderProgramOrange, shaderProgramYellow};
}