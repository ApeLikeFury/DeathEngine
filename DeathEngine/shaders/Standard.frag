#version 430 core

layout(location = 0) out vec4 fragColor;

uniform float iBrightDist;

layout(binding=3) buffer lightsources
{
  float sb_light[];
};

in vec3 VertexNormal;
in vec2 TextureCoordinate;
in vec3 uv;
in vec3 CameraPosition;

uniform sampler2D iTexture;

float GetDiffuse(vec3 Normal, vec3 LightPos, vec3 Coord, float specmap)
{
    vec3 LightVector = normalize(LightPos - Coord);
    float distbr = 1/sqrt(distance(Coord, LightPos)/iBrightDist);
    float Diffuse = max(dot(Normal, LightVector)*distbr, 0.2);

    float specularlight = 5.0;
    vec3 viewdirection = normalize(CameraPosition - Coord);
    vec3 reflectiondirection = reflect(-LightVector, Normal);
    float specamount = pow(max(dot(viewdirection, reflectiondirection), 0.0), 5);
    float specular = specamount * specularlight * specmap;

    return Diffuse; // + specular;
};


void main()
{
    vec3 tex = texture(iTexture, TextureCoordinate).xyz;
    float specmap = (tex.x + tex.y + tex.z)/3;

    float br;

    for (int i = 0; i < sb_light.length(); i+=3)
    {
        vec3 thislightpos = vec3(sb_light[i], sb_light[i+1], sb_light[i+2]);
        br += GetDiffuse(VertexNormal, thislightpos, uv, specmap);
    }

    vec3 col = vec3(br,br,br) * tex;

    fragColor = vec4(col, 1.0);
};