#version 330 core
    
layout(location = 0) in vec4 pos;

uniform mat4 u_MVP;
uniform mat4 u_transform;

void main()
{
    gl_Position = u_MVP * u_transform * pos;
}