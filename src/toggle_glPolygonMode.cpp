#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* state always remains 1-to-1 with which mode is enabled.
	false = GL_FILL
	true = GL_LINE
*/
static bool isPolygon = false;

/* Toggle Polygon mode and return new isPolygon value */
bool toggle_glPolygonMode() {
	if (isPolygon) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	isPolygon = !isPolygon;
	return isPolygon;
}


bool isPolygonMode() {
	return isPolygon;
}