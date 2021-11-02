#version 430 core

layout(location = 0) out vec4 fragColor;

in vec3 VertexNormal;
in vec2 TextureCoordinate;
in vec3 FragmentCoordinate;
in vec3 LightPosition;
in vec3 CameraPosition;

uniform sampler2D iTexture;

void main()
{
    vec3 Normal = normalize(VertexNormal);
    vec3 LightVector = normalize(LightPosition - FragmentCoordinate);
    float Diffuse = max(dot(Normal, LightVector), 0.1);

    float SpecularLight = 0.5;
    vec3 ViewDirection = normalize(CameraPosition - FragmentCoordinate);
    vec3 ReflectionDirection = reflect(-LightVector, Normal);
    float SpecAmount = pow(max(dot(ViewDirection, ReflectionDirection), 0.0f), 10);
    float Specular = SpecAmount * SpecularLight;

    vec4 texColor = texture(iTexture, TextureCoordinate);
    vec3 col = texColor.xyz * (Diffuse + Specular);

    fragColor = vec4(col, 1.0);
};
