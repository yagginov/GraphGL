#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top, float aspect, glm::vec3 view) :
	_left(left), _right(right), _bottom(bottom), _top(top), _aspect(aspect),
	_view(1.0f)
{
	_projection = glm::ortho(_left * _aspect, _right * _aspect, _bottom, _top, 0.1f, 10.0f);
	_view = glm::translate(_view, view);
}

void Camera::change_projection_matrix()
{
	_projection = glm::ortho(_left * _aspect, _right * _aspect, _bottom, _top, 0.1f, 10.0f);
}

glm::vec3 Camera::get_mouse_positions(glm::vec3 mouse_position, glm::vec3 window_size)
{
	float normalized_x = mouse_position.x / window_size.x;
	float normalized_y = mouse_position.y / window_size.y;

	float global_x = normalized_x * (_right - _left) * _aspect + _left * _aspect;
	float global_y = _top - normalized_y * (_top - _bottom);

	return glm::vec3(global_x, global_y, 0.0f);
}

void Camera::procces_mouse_scroll(glm::vec3 mouse_position, glm::vec3 window_size, float yoffset)
{
	float scale_factor = 0.1f * (_right - _left);

	float normalized_x = mouse_position.x / window_size.x;
	float normalized_y = mouse_position.y / window_size.y;

	_left += yoffset * scale_factor * normalized_x;
	_right -= yoffset * scale_factor * (1.0f - normalized_x);
	_bottom += yoffset * scale_factor * (1.0f - normalized_y);
	_top -= yoffset * scale_factor * normalized_y;

	change_projection_matrix();
}

glm::mat4 Camera::get_projection_matrix()
{
	return _projection;
}

glm::mat4 Camera::get_view_matrix()
{
	return _view;
}

void Camera::set_aspect(float aspect)
{
	if (_aspect == aspect) { return; }
	_aspect = aspect;
	change_projection_matrix();
}