#pragma once

inline constexpr float orangeColVec[] = { 1.0f, 0.5f, 0.2f, 1.0f };
inline constexpr float yellowColVec[] = { 1.0f, 1.0f, 0.0f, 1.0f };

namespace exercise {
	enum Type {
		DEFAULT_TRIANGLE,
		RECTANGLE,
		TWO_TRIANGLES, // next to each other
		TWO_TRIANGLES_DIFF_COL, // next to each other different color
	};

	extern Type type;
	extern const int glsl_aPosAttribute;
	extern const int glsl_uColorAttribute;

	void draw2TsDiffCol();

	void draw2Ts(int count = 6);

	void drawRectangle();

	// default drawing
	void drawDefaultTriangle();

	// init VAO, VBO, EBO
	void base();

	/* de-allocate resources 
	* VAO, VBO, EBO
	*/
	void clean();
}