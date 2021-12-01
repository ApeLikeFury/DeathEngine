#version 430 core

layout(location = 0) in vec2 position;
layout(location = 2) in vec2 texcoords;

out vec2 uv;
out vec2 TextureCoordinate;

uniform vec2 iPos1;
uniform vec2 iPos2;
uniform vec2 iResolution;

void main()
{

    TextureCoordinate = texcoords;
    uv = position;

    gl_Position = vec4(position.x, position.y, -1, 1);

};