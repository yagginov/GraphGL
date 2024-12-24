#include "circle.h"

VectorCircle::VectorCircle() :
	_shader("Shaders/VertexShader.vs", "Shaders/FragmentShader.fs"),
    _text_arial("Fonts/arial.ttf")
{
    float vertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f
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
void VectorCircle::add_circle(glm::vec3 pos)
{
    _circles.push_back(Circle(pos));
}

void VectorCircle::draw(glm::mat4 projection, glm::mat4 view)
{
    _shader.use();
    _shader.setMat4("projection", projection);
    _shader.setMat4("view", view);

    glBindVertexArray(_vao);
    for (auto& it : _circles)
    {
        it.draw(_shader);
    }
    glBindVertexArray(0);

    _text_arial.before_draw(projection, view);

    for (auto& it : _circles)
    {
        _text_arial.render_text(it.get_name(), it.get_pos().x, it.get_pos().y, 0.008f, glm::vec3(0.0f, 0.0f, 0.0f));
    }

    _text_arial.after_draw();

}

void VectorCircle::draw(glm::mat4 projection, glm::mat4 view, const std::set<int>& s)
{
    _shader.use();
    _shader.setMat4("projection", projection);
    _shader.setMat4("view", view);

    glBindVertexArray(_vao);


    for (const auto& it : s)
    {
        _circles[it].draw(_shader);
    }
    glBindVertexArray(0);

    _text_arial.before_draw(projection, view);

    for (const auto& it : s)
    {
        _text_arial.render_text(_circles[it].get_name(), _circles[it].get_pos().x, _circles[it].get_pos().y, 0.008f, glm::vec3(0.0f, 0.0f, 0.0f));
    }

    _text_arial.after_draw();
}

void VectorCircle::reset_color(std::set<int> select_set)
{
    for (const auto& it : select_set)
    {
        _circles[it].reset_color();
    }
}

long long VectorCircle::size()
{
	return _circles.size();
}

Circle& VectorCircle::operator[](size_t index)
{
    return _circles[index];
}

std::vector<Circle>::iterator VectorCircle::begin()
{
    return _circles.begin();
}

std::vector<Circle>::iterator VectorCircle::end()
{
    return _circles.end();
}