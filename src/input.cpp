#include "input.hpp"

#include <GLFW/glfw3.h>

#include "render-state.hpp"

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
}