#version 430 core

layout(location = 0) out vec4 fragColor;

in vec2 TextureCoordinate;
uniform sampler2D iTexture;

void main()
{
   vec3 tex = texture(iTexture, TextureCoordinate).xyz;
   fragColor = vec4(tex, 1.0);
};