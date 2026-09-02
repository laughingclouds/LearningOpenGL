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

	auto [shaderProgramOrange, shaderProgramYellow] = createShaderPrograms();
	
	exercise::base();
	exercise::base2Ts();

	if (isPolygonMode())
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	const std::unordered_map<exercise::Type, std::function<void()>> drawFunction = {
		{exercise::DEFAULT_TRIANGLE, [] { exercise::drawDefaultTriangle(); }},
		{exercise::RECTANGLE, [] { exercise::drawRectangle(); }},
		{exercise::TWO_TRIANGLES, [] { exercise::draw2Ts(); }},
		{exercise::TWO_TRIANGLES_2VAO_2VBO, [] { exercise::draw2Ts2VAOs2VBOs();  }},
		{exercise::TWO_TRIANGLES_DIFF_COL, [&] { exercise::draw2TsDiffCol(shaderProgramYellow, shaderProgramOrange); }},
	};

	while (!glfwWindowShouldClose(window)) {
		// input
		//processInput(window);

		// rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (exercise::type != exercise::TWO_TRIANGLES_DIFF_COL)
			glUseProgram(shaderProgramOrange);

		// Call draw function
		drawFunction.at(exercise::type)();

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	exercise::clean();
	glDeleteProgram(shaderProgramOrange);
	glDeleteProgram(shaderProgramYellow);

	glfwTerminate();
	return 0;
}