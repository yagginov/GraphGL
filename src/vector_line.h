#pragma once

#include <iostream>
#include <vector>
#include <set>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Line.h"
#include "Shader.h"

class VectorLine
{
private:
	unsigned int _vbo, _ebo, _vao;
	Shader _shader;
	std::vector<Line> _lines;

public:
	VectorLine();
	~VectorLine()
	{
		glDeleteVertexArrays(1, &_vao);
		glDeleteBuffers(1, &_vbo);
		glDeleteBuffers(1, &_ebo);
	}

	void add_line(glm::vec3 posA, glm::vec3 posB);

	void draw(glm::mat4 projection, glm::mat4 view);
	void draw(glm::mat4 projection, glm::mat4 view, const std::set<int>& s);
	long long size();

	Line& operator[](size_t index) {
		return _lines[index];
	}

	std::vector<Line>::iterator begin();

	std::vector<Line>::iterator end();
};