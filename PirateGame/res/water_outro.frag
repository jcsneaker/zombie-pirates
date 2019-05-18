precision highp float;

varying vec2 v_texcoord;

uniform vec2      iResolution;           // viewport resolution (in pixels)
uniform float     iGlobalTime;           // shader playback time (in seconds)

#define TAU 6.28318530718

vec3 caustic(vec2 uv)
{
    vec2 p = mod(uv*TAU, TAU)-250.0;
    float time = iGlobalTime * .5+23.0;

	vec2 i = vec2(p);
	float c = 1.0;
	float inten = .005;

    float t;
    t = time * (1.0 - (3.5 / float(1)));
    i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
    c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),p.y / (cos(i.y+t)/inten)));
    t = time * (1.0 - (3.5 / float(2)));
    i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
    c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),p.y / (cos(i.y+t)/inten)));
    t = time * (1.0 - (3.5 / float(3)));
    i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
    c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),p.y / (cos(i.y+t)/inten)));
    t = time * (1.0 - (3.5 / float(4)));
    i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
    c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),p.y / (cos(i.y+t)/inten)));
    t = time * (1.0 - (3.5 / float(5)));
    i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
    c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),p.y / (cos(i.y+t)/inten)));
    
	c /= float(5);
	c = 1.17-pow(abs(c), 1.4);
	vec3 color = vec3(pow(abs(c), 8.0));
    color = clamp(color + vec3(0.0, 0.35, 0.5), 0.0, 1.0);
    color = mix(color, vec3(1.0,1.0,1.0),0.3);
    
    return color;
}


// perf increase for god ray, eliminates Y
float causticX(float x, float power, float gtime)
{
    float p = mod(x*TAU, TAU)-250.0;
    float time = gtime * .5+23.0;

	float i = p;;
	float c = 1.0;
	float inten = .005;

    float t;
    
    t = time * (1.0 - (3.5 / float(0+1)));
    i = p + cos(t - i) + sin(t + i);
    c += 1.0/length(p / (sin(i+t)/inten));
    
    t = time * (1.0 - (3.5 / float(1+1)));
    i = p + cos(t - i) + sin(t + i);
    c += 1.0/length(p / (sin(i+t)/inten));
    
    t = time * (1.0 - (3.5 / float(2+1)));
    i = p + cos(t - i) + sin(t + i);
    c += 1.0/length(p / (sin(i+t)/inten));
    
    t = time * (1.0 - (3.5 / float(3+1)));
    i = p + cos(t - i) + sin(t + i);
    c += 1.0/length(p / (sin(i+t)/inten));
    
    t = time * (1.0 - (3.5 / float(4+1)));
    i = p + cos(t - i) + sin(t + i);
    c += 1.0/length(p / (sin(i+t)/inten));
    
	c /= float(5);
	c = 1.17-pow(abs(c), power);
    
    return c;
}


float GodRays(vec2 uv)
{
    float light = 0.0;

    light += pow(abs(causticX((uv.x+0.08*uv.y)/1.7+0.5, 1.8, iGlobalTime*0.65)),10.0)*0.05;
    light-=pow((abs(1.0-uv.y)*0.3),2.0)*0.2;
    light += pow(abs(causticX(sin(uv.x), 0.3,iGlobalTime*0.7)),9.0)*0.4; 
    light += pow(abs(causticX(cos(uv.x*2.3), 0.3,iGlobalTime*1.3)),4.0)*0.1;  
        
    light-=pow(abs((1.0-uv.y)*0.3),3.0);
    light=clamp(light,0.0,1.0);
    
    return light;
}

void main()
{
	
    vec3 skyColor = vec3(0.3, 1.0, 1.0);

    vec3 sunLightColor = vec3(1.7, 0.65, 0.65);
    vec3 skyLightColor = vec3(0.8, 0.35, 0.15);
    vec3 indLightColor = vec3(0.4, 0.3, 0.2);
    vec3 horizonColor = vec3(0.0, 0.05, 0.2);
    vec3 sunDirection = normalize(vec3(0.8, 0.8, 0.6));
    
    vec2 p = (-iResolution.xy + 2.0 * gl_FragCoord.xy) / iResolution.y;

    vec3 eye = vec3(0.0, 1.25, 1.5);
    vec2 rot = 6.2831 * (vec2(-0.05 + iGlobalTime * 0.01, 0.0 - sin(iGlobalTime * 0.5) * 0.01) + vec2(1.0, 0.0) * (- iResolution.xy * 0.25) / iResolution.x);
    eye.yz = cos(rot.y) * eye.yz + sin(rot.y) * eye.zy * vec2(-1.0, 1.0);
    eye.xz = cos(rot.x) * eye.xz + sin(rot.x) * eye.zx * vec2(1.0, -1.0);

    vec3 ro = eye;
    vec3 ta = vec3(0.5, 1.0, 0.0);

    vec3 cw = normalize(ta - ro);
    vec3 cu = normalize(cross(vec3(0.0, 1.0, 0.0), cw));
    vec3 cv = normalize(cross(cw, cu));
    mat3 cam = mat3(cu, cv, cw);

    vec3 rd = cam * normalize(vec3(p.xy, 1.0));

    // background
    vec3 color = skyColor;
    float sky = 0.0;

    // terrain marching
    float tmin = 0.1;
    float tmax = 20.0;
    
    sky = clamp(0.8 * (1.0 - 0.8 * rd.y), 0.0, 1.0);
    color = sky * skyColor;
    color += ((0.3*caustic(vec2(p.x,p.y*1.0)))+(0.3*caustic(vec2(p.x,p.y*2.7))))*pow(abs(p.y),4.0);

    // horizon
    color = mix(color, horizonColor, pow(abs(1.0 - pow(abs(rd.y),4.0)), 20.0));       
    
    // special effects
    color += GodRays(p)*mix(skyColor.x,1.0,p.y*p.y)*vec3(0.7,1.0,1.0);
    
    // gamma correction
    vec3 gamma = vec3(0.46);
	vec3 temp4 = pow(abs(color), gamma);
	
	gl_FragColor = vec4(temp4, 1.0);
}