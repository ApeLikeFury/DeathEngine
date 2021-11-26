#version 430 core

layout(location = 0) in vec2 position;
uniform vec3 iCameraPosition;
uniform vec3 iLightPosition;
uniform float iTime;
out vec2 uv;
out vec3 CameraPosition;
out vec3 LightPosition;
out float Time;

vec3 rotate(vec3 coords, vec3 rot, vec3 center)
{
    rot *= 0.01745329;

    mat3 xrot = mat3
    (
        1., 0., 0.,
        0., cos(rot.x), sin(rot.x),
        0., -sin(rot.x), cos(rot.x)
    );

    mat3 yrot = mat3
    (
        cos(rot.y), 0., -sin(rot.y),
        0., 1., 0.,
        sin(rot.y), 0., cos(rot.y)
    );

    mat3 zrot = mat3
    (
        cos(rot.z), sin(rot.z), 0.,
        -sin(rot.z), cos(rot.z), 0.,
        0., 0., 1.
    );

    vec3 newcoords = coords - center;
    newcoords *= xrot;
    newcoords *= yrot;
    newcoords *= zrot;
    return newcoords + center;
};

void main()
{
    Time = iTime;
    LightPosition = rotate(iLightPosition, vec3(0,iTime,0), vec3(0,100,0));

    uv = position;
    CameraPosition = iCameraPosition;
   
    gl_Position.xy = uv;

};