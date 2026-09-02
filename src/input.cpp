#include <array>
#include <utility>

#include "input.hpp"

#include <GLFW/glfw3.h>

#include "exercise.hpp"
#include "render-state.hpp"

void processInput(GLFWwindow* window) {
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS) return; // act only on key press not release/repeat/etc.

	const bool ctrlPressed = (mods & GLFW_MOD_CONTROL) != 0;

	if (ctrlPressed && (key == GLFW_KEY_Q)) {
		glfwSetWindowShouldClose(window, true);
		return;
	}

	if (ctrlPressed && (key == GLFW_KEY_P)) {
		toggle_glPolygonMode();
		return;
	}

	if (ctrlPressed) {
		static constexpr std::array exerciseBindings = {
			std::pair{GLFW_KEY_0, exercise::DEFAULT_TRIANGLE},
			std::pair{GLFW_KEY_1, exercise::RECTANGLE},
			std::pair{GLFW_KEY_2, exercise::TWO_TRIANGLES},
			std::pair{GLFW_KEY_3, exercise::TWO_TRIANGLES_2VAO_2VBO},
			std::pair{GLFW_KEY_4, exercise::TWO_TRIANGLES_DIFF_COL},
		};

		for (const auto& [boundKey, exerciseType] : exerciseBindings) {
			if (key == boundKey) {
				exercise::type = exerciseType;
				return;
			}
		}
	}
}