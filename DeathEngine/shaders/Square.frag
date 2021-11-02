#version 430 core

layout(location = 0) out vec4 fragColor;

in vec2 uv;
uniform float radius;
uniform vec2 centre;

uniform sampler2D iTexture;

void main()
{
    float dist = distance(centre, uv);
    float br = float((dist < radius));
    fragColor = vec4(br ,br ,br , 1.0);
};
