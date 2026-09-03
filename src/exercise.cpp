#include "exercise.hpp"

#include <glad/glad.h>

// vertex data
float vertices[] = {
	// DEFAULT_TRIANGLE / Rectangle
	0.0f, 0.5f, 0.0f,	// 00 - center top
	-0.5f, -0.5f, 0.0f,	// 01 - bottom left
	0.5f, -0.5f, 0.0f,	// 02 - bottom right
	//
	-0.5f, 0.5f, 0.0f,	// 03 - top left
	0.5f, 0.5f, 0.0f,	// 04 - top right
	0.0f, -0.5f, 0.0f,	// 05 - center bottom
	// Triangle T1
	-0.5f, 0.0f, 0.0f,	// 06: T1 - Left
	-0.25f, 0.5f, 0.0f,	// 07: T1 - Top
	0.0f, 0.0f, 0.0f,	// 08: T1 - Right
	// Triangle T2
	0.0f, 0.0f, 0.0f,	// 09: T2 - Left
	0.25f, 0.5f, 0.0f,	// 10: T2 - Top
	0.5f, 0.0f, 0.0f,	// 11: T2 - Right
};

// referencing vertices[]
unsigned int indices[] = {
	// default triangle
	0, 1, 2,
	// rectangle
	3, 1, 2,	// first triangle
	4, 3, 2,	// second triangle
	// Triangle T1
	6, 7, 8,
	// Triangle T2
	9, 10, 11,	// T2
};

static GLuint VBO, VAO, EBO;

namespace exercise {
	Type type = DEFAULT_TRIANGLE;

	// refer shader.cpp for location values
	const int glsl_aPosAttribute = 0;
	const int glsl_uColorAttribute = 20;

	void draw2TsDiffCol() {
		glBindVertexArray(VAO);
		glUniform4fv(glsl_uColorAttribute, 1, orangeColVec); // change color to orange
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(9 * sizeof(GL_UNSIGNED_INT)));
				
		glUniform4fv(glsl_uColorAttribute, 1, yellowColVec); // change color to yellow
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(12 * sizeof(GL_UNSIGNED_INT)));
	}

	void draw2Ts(int count) {
		glBindVertexArray(VAO);
		glUniform4fv(glsl_uColorAttribute, 1, orangeColVec); // change color to orange
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(9 * sizeof(GL_UNSIGNED_INT)));
	}

	void drawRectangle() {
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(3 * sizeof(GL_UNSIGNED_INT)));
	}

	void drawDefaultTriangle() {
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}

	void base() {	
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(glsl_aPosAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(glsl_aPosAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind (VBO remains attached to VAO)
	}

	void clean() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
}