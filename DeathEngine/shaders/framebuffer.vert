#version 430 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texcoords;
out vec2 TextureCoordinate;

void main()
{
    TextureCoordinate = texcoords;
    gl_Position.xy = position;
};