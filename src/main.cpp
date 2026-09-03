#include <functional>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "exercise.hpp"
#include "init.hpp"
#include "input.hpp"
#include "render-state.hpp"
#include "shader.hpp"


int main() {
	
	GLFWwindow* window = initWindow();
	if (window == NULL) {
		return -1;
	}

	glfwSetKeyCallback(window, keyCallback);

	GLuint shaderProgram = createShaderPrograms();
	glUseProgram(shaderProgram);
	// set default color (orange) for most exercises
	glUniform4fv(exercise::glsl_uColorAttribute, 1, orangeColVec);
	
	exercise::base();

	if (isPolygonMode())
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	const std::unordered_map<exercise::Type, std::function<void()>> drawFunction = {
		{exercise::DEFAULT_TRIANGLE, [] { exercise::drawDefaultTriangle(); }},
		{exercise::RECTANGLE, [] { exercise::drawRectangle(); }},
		{exercise::TWO_TRIANGLES, [] { exercise::draw2Ts(); }},
		{exercise::TWO_TRIANGLES_DIFF_COL, [&] { exercise::draw2TsDiffCol(); }},
	};

	while (!glfwWindowShouldClose(window) && !isError()) {
		// input
		//processInput(window);

		// rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Call draw function
		drawFunction.at(exercise::type)();

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	exercise::clean();
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}