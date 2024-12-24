#include "circle.h"

Circle::Circle(glm::vec3 pos) : _pos(pos), _color(glm::vec3(1.0f, 1.0f, 1.0f)),
_thickness(1.0f), _fade(0.015f), _borderSize(0.055f), _first_point(pos)
{
    static int a = 1;
    name = std::to_string(a);
    ++a;
}

glm::vec3 Circle::get_pos()
{
    return _pos;
}

void Circle::set_pos(glm::vec3 pos)
{
    _pos = _first_point + pos;
}

void Circle::set_first_point()
{
    _first_point = _pos;
}

std::string Circle::get_name()
{
    return name;
}

void Circle::draw(Shader& shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _pos);
    shader.setMat4("model", model);

    shader.setVec3("color_circle", _color);
    shader.setFloat("thickness", _thickness);
    shader.setFloat("borderSize", _borderSize);
    shader.setFloat("fade", _fade);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool Circle::check_hit(glm::vec3 pos)
{
    glm::vec3 vector = _pos - pos;
    float distance = glm::length(vector);
    return distance < 1.0f;
}

void Circle::set_color(glm::vec3 color)
{
    _color = color;
}

void Circle::reset_color()
{
    _color = glm::vec3(1.0f, 1.0f, 1.0f);
}