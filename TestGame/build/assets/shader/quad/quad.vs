#version 400 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float textureIndex;

out vec4 v_color;
out vec2 v_texCoord;
flat out  float v_textureIndex;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(pos, 1.0);
    v_color = color;
    v_texCoord = texCoord;
    v_textureIndex = textureIndex;
}