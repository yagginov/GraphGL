#version 330 core

out vec4 FragColor;

in vec2 posPoint;

uniform float thickness;
uniform float fade;
uniform float borderSize;
uniform vec3 color_circle;

void main()
{
    float distance = 1.0f - length(posPoint);

    vec4 col = vec4(smoothstep(0.0f, fade, distance));
    col *= vec4(1.0f - smoothstep(thickness, thickness + fade, distance));

    vec3 borderCol = vec3(smoothstep(0.0f, fade, distance));
    borderCol *= vec3(smoothstep(borderSize, borderSize + fade, distance));

    col.xyz *= borderCol;
    FragColor = vec4(col * vec4(color_circle, 1.0f));

}
