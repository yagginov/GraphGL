#pragma once
#include <GL/glew.h>

#include <vector>
#include <set>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Circle
{
private:
	glm::vec3 _pos;
	glm::vec3 _first_point;

	glm::vec3 _color;
	float _thickness;
	float _fade;
	float _borderSize;

	std::string name;

public:
	std::set<int> edgesA;
	std::set<int> edgesB;

	Circle(glm::vec3 pos);

	glm::vec3 get_pos();
	void set_pos(glm::vec3 pos);
	void set_first_point();

	bool check_hit(glm::vec3 pos);
	void set_color(glm::vec3 color);
	void reset_color();
	std::string get_name();

	void draw(Shader& shader);
};