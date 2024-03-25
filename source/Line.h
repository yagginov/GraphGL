#pragma once

#include <GL/glew.h>

#include <vector>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"

class Line
{
private:
	glm::vec3 _posA;
	glm::vec3 _posB;
	glm::ivec2 _rel;

	glm::mat4 _model;

	float _fade;
	float _thickness;
	glm::vec3 _color;

public:
	Line(glm::vec3 posA, glm::vec3 posB);

	void change_model_matrices();
	void set_posA(glm::vec3 pos);
	void set_posB(glm::vec3 pos);
	void set_rel(glm::ivec2 rel);
	glm::ivec2 get_rel();

	void draw(Shader &shader);

};