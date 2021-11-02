#version 430 core

layout(location = 0) out vec4 fragColor;

in vec2 uv;

uniform sampler2D iTexture;

void main()
{
    fragColor = vec4(uv.x ,uv.y ,1.0 , 1.0);
};
