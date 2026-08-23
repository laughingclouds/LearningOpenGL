#pragma once

namespace exercise {
	enum Type {
		DEFAULT_TRIANGLE,
	};

	extern Type type;

	// default drawing
	void drawDefaultTriangle();

	// init VAO, VBO, EBO
	void base();

	/* de-allocate resources 
	* VAO, VBO, EBO
	*/
	void clean();
}