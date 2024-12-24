#version 330 core

out vec4 FragColor;

in vec2 posPoint;

uniform float fade;
uniform vec3 color_line;

void main()
{
    float dis_y = 0.5f - length(vec2(0.0f, posPoint.y));

    vec4 col = vec4(1.0f);
    col *= vec4(smoothstep(0.0f, fade, dis_y));

    FragColor = vec4(col * vec4(color_line, 1.0f));

}
