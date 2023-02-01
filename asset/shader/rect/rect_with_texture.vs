#version 330 core
    
layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;
layout(location = 1) in vec2 texCoord;

out vec4 v_color;
out vec2 v_texCoord;

uniform mat4 u_MVP;
// uniform mat4 u_transform;

void main()
{
    // gl_Position = u_MVP * u_transform * pos;
    gl_Position = u_MVP * vec4(pos, 1.0);
    v_color = color;
    v_texCoord = texCoord;
}