#version 330 core
    
layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 u_MVP;
uniform mat4 u_transform;

void main()
{
    gl_Position = u_MVP * u_transform * pos;
    v_texCoord = texCoord;
}