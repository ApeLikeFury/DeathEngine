#version 430 core

layout(location = 0) out vec4 fragColor;

in vec3 VertexNormal;
in vec2 TextureCoordinate;
in vec3 FragmentCoordinate;
in vec3 LightPosition;
in vec3 CameraPosition;

uniform sampler2D iTexture;

layout(binding=0) buffer vertexpositions
{
  float vertices[];
};

layout(binding=1) buffer vertexnormals
{
  float normals[];
};

vec3 brightness(vec3 coords, vec3 n, vec3 light)
{
    vec3 lightvector = normalize(coords-light);
    float diffuse = dot(n, lightvector);
    float dist = distance(light, coords);
    float multiplier = 1.0/sqrt(dist/100);
    float br = diffuse * multiplier;
    return vec3(br, br, br);
}

vec3 SurfaceNormal(vec3 A, vec3 B, vec3 C)
{
    vec3 AB = B - A;
    vec3 AC = C - A;
    return normalize(cross(AB, AC));
}

vec3 Q;

bool Intersects(vec3 A, vec3 B, vec3 C, vec3 RayPos, vec3 RayDir)
{
    vec3 NewPos = RayPos + RayDir * 0.01;

    vec3 n = SurfaceNormal(A,B,C);

    float d = dot(n, A);
    
    float nd = dot(n, RayDir);
    
    if(nd <= 0.0)
    {
        return false;
    }
    
    float t = (d-dot(n,NewPos))/nd;
    
    if(t <= 0.0 )
    {
        return false;
    }
   
    Q = NewPos + (RayDir * t);
    
    float PA = dot(cross(B - A, Q - A), n);
    float PB = dot(cross(C - B, Q - B), n);
    float PC = dot(cross(A - C, Q - C), n);
    
    if(PA >= 0.0 && PB >= 0.0 && PC >= 0.0)
    {
        return true;
    }
    return false;
}

vec3 BaseBrightness()
{
    return brightness(FragmentCoordinate, VertexNormal, LightPosition);
}

vec3 color;

void main()
{
    vec3 CamVector = normalize(CameraPosition - FragmentCoordinate);
    vec3 RayVector = reflect(-CamVector, VertexNormal);
    color = vec3(0.0,0.0,0.0);

    for(int i = 0;i < vertices.length();i += 9)
    {
        vec3 v1 = vec3(vertices[i],vertices[i+1],vertices[i+2]);
        vec3 v2 = vec3(vertices[i+3],vertices[i+4],vertices[i+5]);
        vec3 v3 = vec3(vertices[i+6],vertices[i+7],vertices[i+8]);
        vec3 n = vec3(normals[i],normals[i+1],normals[i+2]);

        if(Intersects(v1, v2, v3, FragmentCoordinate, RayVector))
        {
            color = brightness(Q, n, LightPosition);
            break;
        }
    }

    vec4 texColor = texture(iTexture, TextureCoordinate);
    vec3 col = BaseBrightness();

    fragColor = vec4(col, 1.0);
};