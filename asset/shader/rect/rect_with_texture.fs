#version 330 core
    
layout(location = 0) out vec4 color;

//texCoords from test.vs
in vec2 v_texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;


void main()
{
    color = texture(u_texture, v_texCoord) * u_color;
}