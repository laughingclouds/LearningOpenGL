#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "init.hpp"
#include "input.hpp"
#include "render-state.hpp"
#include "shader.hpp"


int main() {
	
	GLFWwindow* window = initWindow();
	unsigned int shaderProgram = createShaderProgram();
	
	// vertex data
	float vertices[] = {
		0.5f, 0.5f, 0.0f,	// 0 - top right
		0.5f, -0.5f, 0.0f,	// 1 - bottom right
		-0.5f, -0.5f, 0.0f,	// 2 - bottom left
		-0.5f, 0.5f, 0.0f,	// 3 - top left
		0.0f, -0.5f, 0.0f,	// 4 - center bottom
		0.0f, 0.5f, 0.0f,	// 5 - center top
	};

	unsigned int indices[] = {
		3, 2, 4, // first triangle
		0, 4, 1 // second triangle
	};

	unsigned int VBO, VAO, EBO;
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

	if (isPolygonMode())
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// rendering commands
		glClearColor(0.2f, 0.3, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}