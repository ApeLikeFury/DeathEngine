#version 430 core

layout(location = 0) out vec4 fragColor;
uniform float radius;
uniform vec2 centre;
uniform vec3 color;
in vec2 coords;


void main()
{
    float dist = distance(centre, coords);
    if(dist > radius)
    {
        discard;
    }
    fragColor = vec4(color, 1.0);
};
