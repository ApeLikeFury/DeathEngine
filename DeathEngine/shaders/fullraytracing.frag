#version 430 core

layout(location = 0) out vec4 fragColor;
in vec3 CameraPosition;
in vec3 LightPosition;
in vec2 uv;
in float Time;

layout(binding=0) buffer vertexpositions
{
  float vertices[];
};

layout(binding=1) buffer vertexnormals
{
  float normals[];
};

layout(binding=2) buffer randomnumbers
{
  float rand[];
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
    float Diffuse = max(dot(Normal, LightVector), 0.1);

    float specularlight = 0.5;
    vec3 viewdirection = normalize(CameraPosition - Coord);
    vec3 reflectiondirection = reflect(-LightVector, Normal);
    float specamount = pow(max(dot(viewdirection, reflectiondirection), 0.0), 8);
    float specular = specamount * specularlight;

    return Diffuse + specular;
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
        float rand1 = random(vec2(Time/2+uv.x, Time+uv.y));
        float rand2 = random(vec2(Time+uv.x, Time/2+uv.y));
        ray.reflection = reflect(RayDir, normal) + vec3(rand2,rand1,rand2);
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
            br = max(br, 0.1);
            color = vec3(br,br,br);
            finalray = ray;
        }
    }
    
    finalray.color = color;

    return finalray;
}

rayinfo GetShadow(vec3 StartPosition, vec3 lightpos)
{
    float rand1 = random(vec2(Time/2+uv.x, Time+uv.y));
    float rand2 = random(vec2(Time+uv.x, Time/2+uv.y));
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
    vec3 col = vec3(0,0,0);

    int bounces = 2;

    rayinfo ray;
    rayinfo shadow;
    ray.position = CameraPosition;
    ray.reflection = vec3(uv,1);
    for(int i = 0; i < bounces; i++)
    {
        ray = raytrace(ray.position, ray.reflection);

        shadow = GetShadow(ray.position, LightPosition);

        col += ray.color/(i+1);
        
        if(shadow.hit)
        {
            col *= 0.3;
        }
    }


    fragColor = vec4(col, 1.0);
};