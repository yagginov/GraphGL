#include "Line.h"

Line::Line(glm::vec3 posA, glm::vec3 posB):
_posA(posA), _posB(posB),
_fade(0.15f), _thickness(0.13f),
_color(glm::vec3(0.0f, 0.0f, 0.0f))
{
    change_model_matrices();
}


void Line::change_model_matrices()
{
    _model = glm::mat4(1.0f);

    // Знаходимо середину лінії
    glm::vec3 center = (_posA + _posB) / 2.0f;

    // Вираховуємо вектор, який вказує напрямок від початку до кінця лінії
    glm::vec3 direction = _posA - _posB;

    // Обчислюємо кут між напрямком і віссю X
    float angle = glm::degrees(glm::atan(direction.y, direction.x));

    // Масштабуємо квадрат по довжині лінії
    float length = glm::length(direction) - 2.0f;

    // Генеруємо матрицю моделі
    _model = glm::translate(_model, center);
    _model = glm::rotate(_model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    _model = glm::scale(_model, glm::vec3(length, _thickness, 0.0f));

}

void Line::draw(Shader& shader)
{
    shader.setMat4("model", _model);
    shader.setVec3("color_line", _color);
    shader.setFloat("thickness", _thickness);
    shader.setFloat("fade", _fade);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void Line::set_posA(glm::vec3 pos)
{
    _posA = pos;
    change_model_matrices();
}

void Line::set_posB(glm::vec3 pos)
{
    _posB = pos;
    change_model_matrices();
}

void Line::set_rel(glm::ivec2 rel)
{
    _rel = rel;
}
glm::ivec2 Line::get_rel()
{
    return _rel;
}