#ifndef TRANSPARENT_SQUARE_H
#define TRANSPARENT_SQUARE_H

#include <GL/glew.h>

#include "shader.h"

class TransparentSquareRenderer
{
private:
	unsigned int _vbo, _ebo, _vao;
	Shader _shader;
	glm::vec4 _color;
	glm::vec2 _posA, _posB;

	glm::mat4 _model;
	bool select;
	bool access;

	void update_model();

public:
	TransparentSquareRenderer();

	void set_posA(glm::vec2 pos);
	void set_posB(glm::vec2 pos);
	glm::vec4 get_borders();

	void set_select(const bool b);
	bool get_select();

	void set_access(const bool b);
	bool get_access();

	void draw(glm::mat4 projection, glm::mat4 view);
};

#endif		// TRANSPARENT_SQUARE_H