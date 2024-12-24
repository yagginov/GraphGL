#version 330 core
layout (location = 0) in vec2 aPos; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 posPoint;

void main()
{
    posPoint = aPos;
    gl_Position = projection * view * model * vec4(aPos, 0.0f, 1.0f);
}
