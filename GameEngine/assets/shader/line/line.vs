#version 400 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;

out vec4 v_color;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(pos, 1.0);
    v_color = color;
}