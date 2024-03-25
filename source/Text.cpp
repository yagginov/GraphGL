#include "Text.h"


Text::Text(const std::string& filename): 
_shader("Shaders/VertexShader_text.vs", "Shaders/FragmentShader_text.fs")
{
    float vertices[] = {
         0.0f,  0.0f, 0.0f, 1.0f,
         1.0f,  0.0f, 1.0f, 1.0f,
         1.0f,  1.0f, 1.0f, 0.0f,
         0.0f,  1.0f, 0.0f, 0.0f
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

    glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //// Init Library FreeType
    FT_Library ft;
    FT_Init_FreeType(&ft);

    //// Load font in face
    FT_Face face;
    if (FT_New_Face(ft, filename.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    else {
        //// Change size for loading glyphs
        FT_Set_Pixel_Sizes(face, 0, 128);

        //// Disabling byte alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        //// Loading character glyphs
        for (unsigned int c = 0; c < 256; c++)
        {
            //// Load character glyphs
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }

            //// Generating texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            //// Set the necessary options for the texture
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            //// Now save the symbol for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            _characters.push_back(character);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    //// Freeing up used resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

}

void Text::render_text(std::string text, float x, float y, float scale, glm::vec3 color)
{
    //// Align the text to the center of a given point
    unsigned int u_width = 0;
    int i_height = 0;
    for (const auto& it : text)
    {
        u_width += _characters[(int)it].Advance;
        i_height = std::max(_characters[(int)it].Size.y, i_height);
    }

    float width = (u_width >> 6) * scale;
    width /= 2.0f;
    float height = (i_height * scale) / 2.0f;

    x -= width;
    y -= height;

    // Setuping color for the text	
    _shader.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);

    for (const auto& it : text)
    {
        Character ch = _characters[(int)it];

        //// Creating model matrix for the character
        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(xpos, ypos, 0.0f));
        model = glm::scale(model, glm::vec3(w, h, 0.0f));

        _shader.setMat4("model", model);

        //// Render the glyph texture onto a rectangle
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //// Moving to the next character
        x += (ch.Advance >> 6) * scale; 
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::before_draw(glm::mat4 projection, glm::mat4 view)
{
    _shader.use();
    _shader.setMat4("projection", projection);
    _shader.setMat4("view", view);

    glBindVertexArray(_vao);
}

void Text::after_draw()
{
    glBindVertexArray(0);
}

