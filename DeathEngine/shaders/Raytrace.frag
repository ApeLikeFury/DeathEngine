#version 430 core

layout(location = 0) out vec4 fragColor;

layout(binding=0) buffer vertexpositions
{
  float vertices[];
};

uniform vec3 iLightPosition;
uniform vec3 iCameraPosition;
in vec2 uv;

vec3 color;

vec3 v4 = vec3( 0.5,  0.5, 1.0);
vec3 v5 = vec3( 0.5, -0.5, 2.5);
vec3 v6 = vec3( 0.5, -0.5, 1.0);

float brightness(vec3 coords, vec3 n, vec3 light)
{
    vec3 lightvector = normalize(coords-light);
    float diffuse = dot(n, lightvector);
    float dist = distance(light, coords);
    float multiplier = 1.0/sqrt(dist/100);
    return diffuse * multiplier;
}

vec3 SurfaceNormal(vec3 A, vec3 B, vec3 C)
{
    vec3 AB = B - A;
    vec3 AC = C - A;
    return normalize(cross(AB, AC));
}

bool Intersects(vec3 A, vec3 B, vec3 C, vec3 RayPos, vec3 RayDir)
{
    vec3 n = SurfaceNormal(A,B,C);

    float d = dot(n, A);
    
    float nd = dot(n, RayDir);
    
    if(nd <= 0.0)
    {
        return false;
    }
    
    float t = (d-dot(n,RayPos))/nd;
    
    if(t <= 0.0 )
    {
        return false;
    }
   
    vec3 Q = RayPos + (RayDir * t);
    
    float PA = dot(cross(B - A, Q - A), n);
    float PB = dot(cross(C - B, Q - B), n);
    float PC = dot(cross(A - C, Q - C), n);
    
    if(PA >= 0.0 && PB >= 0.0 && PC >= 0.0)
    {
        float br = brightness(Q, n, iLightPosition);
        color = vec3(br, br, br);
        return true;
    }
    return false;
}

void main()
{
    color = vec3(0.2, 0, 0);

    vec3 pos = vec3(iCameraPosition.x,iCameraPosition.y,iCameraPosition.z);

    for (int i = 0; i < vertices.length(); i += 9)
    {
        vec3 v1 = vec3(vertices[i], vertices[i+1], vertices[i+2]);
        vec3 v2 = vec3(vertices[i+3], vertices[i+4], vertices[i+5]);
        vec3 v3 = vec3(vertices[i+6], vertices[i+7], vertices[i+8]);
        Intersects(v1, v2, v3, pos, vec3(uv, 1));
    }

    fragColor = vec4(color, 1.0);
}