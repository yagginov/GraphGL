#pragma once

#include <iostream>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Circle.h"
#include "Shader.h"
#include "Text.h"

class VectorCircle
{
private:
	unsigned int _vbo, _ebo, _vao;
	Shader _shader;
	std::vector<Circle> _circles;
	Text _text_arial;

public:
	VectorCircle();
	~VectorCircle()
	{
		glDeleteVertexArrays(1, &_vao);
		glDeleteBuffers(1, &_vbo);
		glDeleteBuffers(1, &_ebo);
	}

	void add_circle(glm::vec3 posA);

	void draw(glm::mat4 projection, glm::mat4 view);
	void draw(glm::mat4 projection, glm::mat4 view, const std::set<int>& s);
	long long size();
	void reset_color(std::set<int> select_set);

	Circle& operator[](size_t index);

	std::vector<Circle>::iterator begin();

	std::vector<Circle>::iterator end();
};