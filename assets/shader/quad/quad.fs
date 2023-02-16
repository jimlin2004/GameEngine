#version 400 core
    
layout(location = 0) out vec4 color;

//from quad.vs
in vec4 v_color;
in vec2 v_texCoord;
flat in  float v_textureIndex;

uniform sampler2D u_textures[32];

void main()
{
    color = texture(u_textures[int(v_textureIndex)], v_texCoord) * v_color;
}