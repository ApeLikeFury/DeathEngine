#version 430 core

layout(location = 0) out vec4 fragColor;

in vec3 VertexNormal;
in vec2 TextureCoordinate;
in vec3 uv;
in vec3 LightPosition;
in vec3 CameraPosition;

uniform sampler2D iTexture;

float GetDiffuse(vec3 Normal, vec3 LightPos, vec3 Coord)
{
    vec3 LightVector = normalize(LightPos - Coord);
    float distbr = 1/sqrt(distance(Coord, LightPos)/10000);
    float Diffuse = max(dot(Normal, LightVector)*distbr, 0.1);

    float specularlight = 0.5;
    vec3 viewdirection = normalize(CameraPosition - Coord);
    vec3 reflectiondirection = reflect(-LightVector, Normal);
    float specamount = pow(max(dot(viewdirection, reflectiondirection), 0.0), 8);
    float specular = specamount * specularlight;

    return Diffuse + specular;
};




void main()
{
   float br = GetDiffuse(VertexNormal, LightPosition, uv);
   vec3 texCoord = texture(iTexture, TextureCoordinate).xyz;
   vec3 col = vec3(br,br,br) * texCoord;

    fragColor = vec4(col, 1.0);
};