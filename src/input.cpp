#include <array>

#include "input.hpp"

#include <GLFW/glfw3.h>

#include "render-state.hpp"
#include "exercise.hpp"

static void processExerciseSelection(GLFWwindow* window, bool ctrlPressed) {
	if (!ctrlPressed)
		return;

	static constexpr std::array exerciseBindings = {
		std::pair{GLFW_KEY_0, exercise::DEFAULT_TRIANGLE},
		std::pair{GLFW_KEY_1, exercise::RECTANGLE},
		std::pair{GLFW_KEY_2, exercise::TWO_TRIANGLES},
		std::pair{GLFW_KEY_3, exercise::TWO_TRIANGLES_2VAO_2VBO},
	};

	for (const auto& [key, type] : exerciseBindings) {
		if (glfwGetKey(window, key) == GLFW_PRESS) {
			exercise::type = type;
			break;
		}
	}
}

void processInput(GLFWwindow* window) {
	static bool key_p_ispress = false;

	bool key_ctrl_ispress =
		(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) ||
		(glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS);

	if (key_ctrl_ispress && (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)) {
		glfwSetWindowShouldClose(window, true);
	}

	// enter only if key was not pressed before
	if (key_ctrl_ispress && !key_p_ispress && (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)) {
		toggle_glPolygonMode();
		key_p_ispress = true; // now key is in "pressing" state
		// don't enter if-block again till the key is released
	}

	if ((glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)) {
		key_p_ispress = false; // key no longer pressed
	}

	processExerciseSelection(window, key_ctrl_ispress);
}