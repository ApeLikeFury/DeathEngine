#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texcoords;

out vec3 VertexNormal;
out vec3 LightPosition;
out vec3 uv;
out vec2 TextureCoordinate;
out vec3 CameraPosition;

uniform vec3 iCameraPosition;
uniform vec3 iCameraRotation;
uniform vec3 iPlayerPosition;

uniform vec3 iObjectRotation;
uniform vec3 iObjectLocation;
uniform vec3 iObjectCentre;

uniform vec2 iScreenResolution;
uniform vec3 iLightPosition;
uniform float iTime;


float fov = 1;

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
    uv = position*1000;
    uv.xz *= iScreenResolution.y / iScreenResolution.x;

    vec3 ry = rotate(uv, vec3(0,iCameraRotation.y,0), iCameraPosition);
    vec3 rx = rotate(ry, vec3(iCameraRotation.x,0,0), iCameraPosition);
    vec3 vp = rx - iCameraPosition;
    VertexNormal = normals;
    TextureCoordinate = texcoords;
    CameraPosition = iCameraPosition;
    LightPosition = iLightPosition;

    gl_Position = vec4(vp.x, vp.y, -1, vp.z/fov);

};