#version 330 core
    
layout(location = 0) out vec4 color;

//from rect_with_texture.vs
in vec4 v_color;
in vec2 v_texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
    // color = texture(u_texture, v_texCoord) * u_color;
    color = v_color;
}