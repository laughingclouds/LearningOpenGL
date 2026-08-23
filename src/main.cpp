#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "init.hpp"
#include "input.hpp"
#include "render-state.hpp"
#include "shader.hpp"
#include "exercise.hpp"


int main() {
	
	GLFWwindow* window = initWindow();
	if (window == NULL) {
		return -1;
	}

	unsigned int shaderProgram = createShaderProgram();
	
	exercise::base();
	exercise::base2Ts();

	if (isPolygonMode())
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		if (exercise::type == exercise::DEFAULT_TRIANGLE) {
			exercise::drawDefaultTriangle();
		}
		else if (exercise::type == exercise::RECTANGLE) {
			exercise::drawRectangle();
		}
		else if (exercise::type == exercise::TWO_TRIANGLES) {
			exercise::draw2Ts();
		}
		else if (exercise::type == exercise::TWO_TRIANGLES_2VAO_2VBO) {
			exercise::draw2Ts2VAOs2VBOs();
		}

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	exercise::clean();
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}