#version 400 core
    
layout(location = 0) out vec4 color;
layout(location = 1) out int entityID;

//from quad.vs
in vec4 v_color;
in vec2 v_texCoord;
flat in float v_textureIndex;
flat in int v_entityID;

uniform sampler2D u_textures[32];

void main()
{
    vec4 texColor = v_color * texture(u_textures[int(v_textureIndex)], v_texCoord);

    if (texColor.a == 0.0)
        discard;

    color = texColor;

    entityID = v_entityID;
}