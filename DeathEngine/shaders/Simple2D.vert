#version 430 core

layout(location = 0) in vec3 position;
out vec2 uv;

void main()
{
    uv = position.xy;
   
    gl_Position.xy = vec2(uv.x, uv.y);

};