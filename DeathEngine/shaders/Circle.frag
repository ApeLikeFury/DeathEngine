#version 430 core

layout(location = 0) out vec4 fragColor;

in vec2 uv;
in float rad;
in vec2 cen;

void main()
{
    vec3 br = vec3(0,0,0);
    float dist = distance(cen, uv);
    if(dist < rad)
    {
        br = vec3(1,1,1);
    }
    fragColor = vec4(br, 1.0);
};
