#pragma once

#include <GL/glew.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
	glm::mat4 _projection;
	glm::mat4 _view;

	float _left, _right, _bottom, _top;
	float _aspect;

	void change_projection_matrix();

public:
	Camera(float left, float right, float bottom, float top, float aspect, glm::vec3 view);

	glm::vec3 get_mouse_positions(glm::vec3 mouse_positions, glm::vec3 window_size);
	void procces_mouse_scroll(glm::vec3 mouse_positions, glm::vec3 window_size, float yoffset);
	glm::mat4 get_projection_matrix();
	glm::mat4 get_view_matrix();
	void set_aspect(float aspect);
};