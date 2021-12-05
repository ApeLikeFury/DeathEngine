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

layout(binding=2) buffer vertextexcoords
{
  float texcoords[];
};

layout(binding=3) buffer lightsources
{
  float sb_light[];
};

vec2 InterpolateTexcoords(vec2 vt1, vec2 vt2, vec2 vt3, vec3 barycentric)
{
    return vt1*barycentric.x + vt2*barycentric.y + vt3*barycentric.z;
}

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
    vec3 barycentric;
};

float GetDiffuse(vec3 Normal, vec3 LightPos, vec3 Coord)
{
    vec3 LightVector = normalize(LightPos - Coord);
    float distbr = 1/sqrt(distance(Coord, LightPos)/10);
    float Diffuse = max(dot(Normal, LightVector)*distbr, 0.1);

    float specularlight = 0.5;
    vec3 viewdirection = normalize(CameraPosition - Coord);
    vec3 reflectiondirection = reflect(-LightVector, Normal);
    float specamount = pow(max(dot(viewdirection, reflectiondirection), 0.0), 8);
    float specular = specamount * specularlight;

    return Diffuse + specular;
};

rayinfo Intersection(vec3 v0, vec3 v1, vec3 v2, vec3 RayPos, vec3 RayDir)
{
    RayPos += RayDir*0.00001;
    rayinfo ray;
    ray.hit = false;

    vec3 v0v1 = v1-v0;
    vec3 v0v2 = v2-v0;
    vec3 n = cross(v0v1, v0v2);
    float area = length(n)/2;
    n = normalize(n);

    float d = dot(n, v0);
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
   
    vec3 P = RayPos + (RayDir * t);


    vec3 C;
    vec3 edge0 = v1 - v0;
    vec3 vp0 = P - v0;
    C = cross(edge0, vp0);
    if(dot(n,C) < 0) {return ray;}
    vec3 edge1 = v2 - v1;
    vec3 vp1 = P - v1;
    C = cross(edge1, vp1);
    float u = (length(C)/2)/area;
    if(dot(n,C) < 0) {return ray;}
    vec3 edge2 = v0 - v2;
    vec3 vp2 = P - v2;
    C = cross(edge2, vp2);
    float v = (length(C)/2)/area;
    if(dot(n,C) < 0) {return ray;}
    
    
    ray.hit = true;
    ray.position = P;
    ray.normal = n;
    ray.origindist = t;
    //ray.reflection = reflect(RayDir, n);
    ray.barycentric = vec3(u,v,1-(u+v));
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

        int ti = (i/9)*6;
        vec2 vt1 = vec2(texcoords[ti], texcoords[ti+1]);
        vec2 vt2 = vec2(texcoords[ti+2], texcoords[ti+3]);
        vec2 vt3 = vec2(texcoords[ti+4], texcoords[ti+5]);
    
        ray = Intersection(v1, v2, v3, StartPosition, RayDirection);

        if(ray.hit && ray.origindist < dist)
        {
            dist = ray.origindist;

            float br;

            for (int i = 0; i < sb_light.length(); i+=3)
            {
                 vec3 thislightpos = vec3(sb_light[i], sb_light[i+1], sb_light[i+2]);
                 br += GetDiffuse(ray.normal, thislightpos, ray.position);
            }

            vec2 tc = InterpolateTexcoords(vt1,vt2,vt3,ray.barycentric);
            vec4 texColor = texture(iTexture, tc);
            color = vec3(br,br,br)*texColor.xyz;
            finalray = ray;
        }
    }

    if(!finalray.hit)
    {
        color = vec3(0.3,0.3,1);
    }
    
    finalray.color = color;

    return finalray;
}

void main()
{
    vec3 camvector = normalize(uv-CameraPosition);
    vec3 lightvector = normalize(uv-LightPosition);

    rayinfo ray;
    ray.reflection = reflect(camvector, VertexNormal);
    for (int i = 0; i < 1; i ++)
    {
       ray = raytrace(uv, ray.reflection);
    }

    vec4 texColor = texture(iTexture, TextureCoordinate);
    vec3 color = GetDiffuse(VertexNormal,LightPosition,uv)/10 + ray.color;
    
    fragColor = vec4(color, 1.0);
};
