#version 430 core

layout(location = 0) out vec4 fragColor;

in vec3 VertexNormal;
in vec2 TextureCoordinate;
in vec3 uv;
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

float random(vec2 co)
{
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

struct rayinfo
{
    bool hit;
    float origindist;
    vec3 color;
    vec3 position;
    vec3 normal;
    vec3 reflection;
};

float GetDiffuse(vec3 Normal, vec3 LightPos, vec3 Coord)
{
    vec3 LightVector = normalize(LightPos - Coord);
    float diffuse = dot(Normal, LightVector);
    return max(diffuse, 0.1);
};


rayinfo Intersection(vec3 A, vec3 B, vec3 C, vec3 normal, vec3 RayPos, vec3 RayDir)
{
    RayPos += RayDir;
    rayinfo ray;
    ray.hit = false;

    vec3 n = normal;

    float d = dot(n, A);
    
    float nd = dot(n, RayDir);
    
    if(nd >= 0.99999)
    {
        return ray;
    }
    
    float t = (d-dot(n,RayPos))/nd;
    
    if(t <= 0.00)
    {
        return ray;
    }
   
    vec3 Q = RayPos + (RayDir * t);
    
    float PA = dot(cross(B - A, Q - A), n);
    float PB = dot(cross(C - B, Q - B), n);
    float PC = dot(cross(A - C, Q - C), n);
    
    if(PA >= 0.0 && PB >= 0.0 && PC >= 0.0)
    {
        ray.hit = true;
        ray.position = Q;
        ray.normal = n;
        ray.origindist = t;
        ray.reflection = reflect(RayDir, normal);
        return ray;
    }
    return ray;
}

rayinfo raytrace(vec3 StartPosition, vec3 RayDirection)
{
    rayinfo ray;
    rayinfo finalray;
    
    vec3 color = vec3(0,0,0);
    float dist = 1000000000;

    for (int i = 0; i < vertices.length(); i += 9)
    {
        vec3 v1 = vec3(vertices[i], vertices[i+1], vertices[i+2]);
        vec3 v2 = vec3(vertices[i+3], vertices[i+4], vertices[i+5]);
        vec3 v3 = vec3(vertices[i+6], vertices[i+7], vertices[i+8]);
        vec3 normal = vec3(normals[i], normals[i+1], normals[i+2]);
    
        ray = Intersection(v1, v2, v3, normal, StartPosition, RayDirection);
        
        if(ray.hit && ray.origindist < dist)
        {
            dist = ray.origindist;
            float br = GetDiffuse(ray.normal, LightPosition, ray.position);
            color = vec3(br,br,br);
            finalray = ray;
        }
    }
    
    finalray.color = color;

    return finalray;
}

rayinfo GetShadow(vec3 StartPosition, vec3 lightpos)
{
    vec3 RayDirection = normalize(lightpos - StartPosition);
    float LightDist = distance(StartPosition, lightpos);

    rayinfo ray;
    
    for (int i = 0; i < vertices.length(); i += 9)
    {
        vec3 v1 = vec3(vertices[i], vertices[i+1], vertices[i+2]);
        vec3 v2 = vec3(vertices[i+3], vertices[i+4], vertices[i+5]);
        vec3 v3 = vec3(vertices[i+6], vertices[i+7], vertices[i+8]);
        vec3 normal = vec3(normals[i], normals[i+1], normals[i+2]);
        
        ray = Intersection(v1, v2, v3, normal, StartPosition, RayDirection);
        
        if(ray.hit && ray.origindist < LightDist)
        {
            break;
        }
    }
    return ray;
}

void main()
{
    vec4 texColor = texture(iTexture, TextureCoordinate);
    vec3 camvector = normalize(uv-CameraPosition);
    vec3 lightvector = normalize(uv-LightPosition);
    float d = GetDiffuse(VertexNormal, LightPosition, uv);

    vec3 color = vec3(d,d,d);

    rayinfo ray;
    for(int i = 0;i < 1; i++)
    {
        vec3 offset = vec3(random(uv.xy+i),random(uv.xz+i),random(uv.yz+i))/40;
        vec3 reflectiondirection = reflect(camvector, VertexNormal) + offset;
        ray = raytrace(uv, reflectiondirection);
        color += ray.color;
    }

    if(GetShadow(uv, LightPosition).hit)
    {
        color *= 0.2;
    }
    

    fragColor = vec4(texColor.xyz*color*1.5, 1.0);
};
