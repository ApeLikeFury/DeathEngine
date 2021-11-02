#version 430 core

layout(location = 0) in vec3 position;
uniform float radius;
uniform vec2 centre;
out vec2 uv;
out float rad;
out vec2 cen;

void main()
{
    rad = radius;
    cen = centre;
    uv = position.xy;
   
    gl_Position.xy = vec2(uv.x, uv.y);

};