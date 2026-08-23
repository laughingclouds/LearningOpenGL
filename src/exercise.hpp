#pragma once

namespace exercise {
	enum Type {
		DEFAULT_TRIANGLE,
		RECTANGLE,
		TWO_TRIANGLES, // next to each other
		TWO_TRIANGLES_2VAO_2VBO, // different VAO, VBO
		TWO_TRIANGLES_DIFF_COL,
	};

	extern Type type;

	void draw2TsDiffCol(unsigned int shaderProg1, unsigned int shaderProg2);

	void draw2Ts2VAOs2VBOs();

	void draw2Ts(int count = 6);

	void drawRectangle();

	// default drawing
	void drawDefaultTriangle();

	void base2Ts();

	// init VAO, VBO, EBO
	void base();

	/* de-allocate resources 
	* VAO, VBO, EBO
	*/
	void clean();
}