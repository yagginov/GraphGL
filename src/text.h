#pragma once
#include <GL/glew.h>

#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H 

#include "shader.h"

struct Character {
    unsigned int TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    unsigned int Advance;
};

class Text
{
private:
    std::vector<Character> _characters;
    Shader _shader;
    unsigned int _vbo, _ebo, _vao;

public:
    Text(const std::string& filename);
    void render_text(std::string text, float x, float y, float scale, glm::vec3 color);
    void before_draw(glm::mat4 projection, glm::mat4 view);
    void after_draw();
};