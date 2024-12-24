#include "vector_line.h"

VectorLine::VectorLine() :
	_shader("shaders/vs_line.shader", "shaders/fs_line.shader")
{
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

void VectorLine::add_line(glm::vec3 posA, glm::vec3 posB)
{
    _lines.push_back(Line(posA, posB));
}

void VectorLine::draw(glm::mat4 projection, glm::mat4 view)
{
    _shader.use();
    _shader.setMat4("projection", projection);
    _shader.setMat4("view", view);

    glBindVertexArray(_vao);
    for (auto& it : _lines)
    {
        it.draw(_shader);
    }
    glBindVertexArray(0);
}

void VectorLine::draw(glm::mat4 projection, glm::mat4 view, const std::set<int>& s)
{
    _shader.use();
    _shader.setMat4("projection", projection);
    _shader.setMat4("view", view);

    glBindVertexArray(_vao);
    for (const auto& it : s)
    {
        _lines[it].draw(_shader);
    }
    glBindVertexArray(0);
}

long long VectorLine::size()
{
    return _lines.size();
}

std::vector<Line>::iterator VectorLine::begin()
{
    return _lines.begin();
}

std::vector<Line>::iterator VectorLine::end()
{
    return _lines.end();
}