#include "transparent_square.h"

TransparentSquareRenderer::TransparentSquareRenderer() :
    _shader("shaders/vs_square.shader", "shaders/fs_square.shader"),
    _posA(0.0f, 0.0f), _posB(0.0f, 0.0f),
    _color(0.867f, 0.867f, 1.0f, 0.5f), access(false), select(false)
{
    update_model();
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    //// Create Vertex Buffer Objects---
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    //// Create Vertex Array Objects---
    glGenVertexArrays(1, &_vao);

    //// Init VBO, VAO-----------------------------------------------------------
    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TransparentSquareRenderer::update_model()
{
    glm::vec2 center = (_posA + _posB) / 2.0f;
    glm::vec2 direction = (_posA - _posB);

    _model = glm::mat4(1.0f);
    _model = glm::translate(_model, glm::vec3(center, 0.0f));
    _model = glm::scale(_model, glm::vec3(direction, 0.0f));
}


void TransparentSquareRenderer::set_posA(glm::vec2 pos)
{
    _posA = pos;
}
void TransparentSquareRenderer::set_posB(glm::vec2 pos)
{
    _posB = pos;
    update_model();
}

glm::vec4 TransparentSquareRenderer::get_borders()
{
    float left, right, up, bottom;

    if (_posA.x < _posB.x)
    {
        left = _posA.x;
        right = _posB.x;
    }
    else
    {
        right = _posA.x;
        left = _posB.x;
    }

    if (_posA.y < _posB.y)
    {
        bottom = _posA.y;
        up = _posB.y;
    }
    else
    {
        up = _posA.y;
        bottom = _posB.y;
    }

    return glm::vec4(left, right, up, bottom);
}

void TransparentSquareRenderer::set_select(const bool b)
{
    select = b;
}
bool TransparentSquareRenderer::get_select()
{
    return select;
}

void TransparentSquareRenderer::set_access(const bool b)
{
    select = b;
}
bool TransparentSquareRenderer::get_access()
{
    return select;
}

void TransparentSquareRenderer::draw(glm::mat4 projection, glm::mat4 view)
{
    _shader.use();
    _shader.setMat4("projection", projection);
    _shader.setMat4("view", view);
    _shader.setMat4("model", _model);
    _shader.setVec4("color", _color);

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);    
}