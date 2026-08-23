#include "exercise.hpp"

#include <glad/glad.h>

// vertex data
float vertices[] = {
	0.0f, 0.5f, 0.0f,	// 0 - center top
	-0.5f, -0.5f, 0.0f,	// 1 - bottom left
	0.5f, -0.5f, 0.0f,	// 2 - bottom right
	-0.5f, 0.5f, 0.0f,	// 3 - top left
	0.5f, 0.5f, 0.0f,	// 4 - top right
	0.0f, -0.5f, 0.0f,	// 5 - center bottom
};

unsigned int indices[] = {
	3, 2, 4, // first triangle
	0, 4, 1 // second triangle
};

static unsigned int VBO, VAO, EBO;

namespace exercise {
	Type type = DEFAULT_TRIANGLE;

	void drawDefaultTriangle() {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void clean() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
}