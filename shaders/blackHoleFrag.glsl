#version 330 core

#define MAX_STEP 1200
#define PI 3.1415926
#define GM 0.8

out vec4 FragColor;

in vec2 v_texCoord;

uniform vec3 camPos;
uniform vec2 resolution;
uniform vec3 pos;
uniform float eventHorizonRadius;

uniform mat4 projection;
uniform mat4 view;

uniform sampler2D u_DiffuseMap;
uniform sampler2D noiseTexture;

uniform float time;

// Whether a point is inside event horizon
float HitTest(vec3 p){
    return length(p) - eventHorizonRadius;
}

// Transfer a light point from world coordinate to screen coordinate (texture uv).
// Then get the texture color with that uv.
vec3 GetBg(vec3 p){
    vec4 texPos = vec4(p, 1.0f);
    texPos = projection * view * texPos;
    vec2 uv = (texPos * 0.03f+ 0.5).xy;
    return texture(u_DiffuseMap, uv).rgb;
}

// Whether to show a accretion disk
float torus_sdf( vec3 p, vec2 t )
{
  vec2 q = vec2(length(p.xz)-t.x,p.y);
  return length(q)-t.y;
}

void main()
{
    // Map pixel coordinate to [-1, 1]
    vec2 uv = v_texCoord * 2.0f - 1.0f;
    
    // Transfer pixels from screen coordinate to world coordinate
    vec3 sd = vec3(uv.x, uv.y, -1.0f);
    vec4 ray_clip = vec4(sd, 1.0f);
    vec4 ray_eye = inverse(projection) * ray_clip;
    vec4 ray_world = inverse(view) * ray_eye;
    
    if(ray_world.w != 0.0f){
        ray_world.x = ray_world.x / ray_world.w;
        ray_world.y = ray_world.y / ray_world.w;
        ray_world.z = ray_world.z / ray_world.w;
    }
    sd = vec3(ray_world.x, ray_world.y, ray_world.z);
    
    // Get ray direction
    vec3 rayDir = normalize(sd - camPos);
    
    
    vec3 col = vec3(0.0f);
        
    float hitbh = 0.;
    
    float st = 0.;
    vec3 p = sd;
    vec3 v = rayDir;
    float dt = 0.02;
    vec3 cp = pos;
    float bc = 0.0f;
    vec3 torCol = vec3(0.0f);
    vec3 jetCol = vec3(0.0f);
    for(int i = 0;i<MAX_STEP;++i)
    {
        // Gravitation lens
        p += v * dt;
        vec3 relP = p - cp;
        float r2 = dot(relP,relP);
        vec3 a = GM/r2 * normalize(-relP);
        v += a * dt;
        float hit = HitTest(relP);
        hitbh = max(hitbh, smoothstep(0.02, -0.05, hit));
        float glow = 0.013/r2;
        bc += glow * (1.0f - hitbh);
        
        // accretion disk
        float rotangle = PI/18.0f;
        mat3 torRot = mat3(
                    vec3(cos(rotangle),-sin(rotangle),0),
                    vec3(sin(rotangle),cos(rotangle),0),
                    vec3(0,0,1)
                );
        vec3 torpos = (torRot * relP);
        
        float tor = torus_sdf(torpos*vec3(1,13.,1.),vec2(1.8,1.2));
        float hitTor = smoothstep(0.0f, -0.01f, tor);
        
        float v = smoothstep(0.,1.,length(torpos.xz)/18.);
        float u = atan(torpos.z,torpos.x)/PI *v -time*0.03;
        
        vec2 toruv = vec2(u,v)*vec2(15,10.1);
        vec3 distor = texture(noiseTexture,toruv).r*vec3(0.9,0.6,0.4);
        float fade = smoothstep(4.,1.5,length(torpos.xz));
        torCol += 0.025 *distor* hitTor*(1.-hitbh)*fade;
        
        //jets
        float jetHeight = smoothstep(0.0f, 2.5f, abs(torpos.y));
        vec3 blue = vec3(0.3f, 0.3f, 0.6f);
        vec3 red = vec3(0.6f, 0.3f, 0.3f);
        float jetWidth = 0.001 / dot(torpos.xz, torpos.xz);
        
        //animation
        float t = time;
        float jetAnim = (0.5*sin(t+sin(t+sin(t+sin(t*2.))))+0.5) ;
        jetAnim = smoothstep(0.5f,0.6f,jetAnim);
        jetAnim = 12.5f*jetAnim;
        
        jetCol += jetWidth*(1.0f-hitbh)
                *mix(blue,red,jetHeight)
                *smoothstep(jetAnim,0.0f, abs(torpos.y));
    }
    col = 0.13f * bc * vec3(0.9f, 0.8f, 0.8f) + GetBg(p) * (1.0f-hitbh);
    col += torCol;
    col += jetCol;
    FragColor = vec4(col, 1.0f);
}
