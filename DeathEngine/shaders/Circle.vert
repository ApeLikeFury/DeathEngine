#version 430 core

layout(location = 0) in vec3 position;
uniform float radius;
uniform vec2 centre;
out vec2 coords;

void main()
{
    coords = position.xy*radius + centre;
   
    gl_Position = vec4(coords, 0.0, 1.0);

};