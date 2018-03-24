#ifdef GL_ES
#define LOWP lowp
precision mediump float;
#else
#define LOWP
#endif

#define PI 3.14

//inputs from vertex shader
varying vec2 vTexCoord0;
varying vec2 vTexCoord1;
varying LOWP vec4 vColor;

uniform vec2 lightLocation;
uniform vec3 lightColor;
uniform float u_radius;
uniform vec2        resolution;
uniform sampler2D   u_texture;
uniform sampler2D   u_objects_tex;

// ----------------------------------------------------------
//sample from the 1D distance map
float sample(vec2 coord, float r) {
    return step(r, texture2D(u_texture, coord).r);
}

// ----------------------------------------------------------
void main() {
    
    
    //rectangular to polar
    vec2 offset     = vec2(lightLocation.x-resolution.x/2.0, lightLocation.y-resolution.y/2.0);
    vec2 inputCoord = (vec2(gl_FragCoord.x-offset.x, resolution.y - (gl_FragCoord.y-offset.y))) / resolution;
    vec2 norm       = inputCoord * 2.0 - 1.0;
    float theta     = atan(norm.y, norm.x);
    float r         = length(norm);
    float coord     = (theta + PI) / (2.0*PI);
    
    vec2 tc = vec2(coord, 0.0);
    
    float center = sample(tc, r);

    
    float intensity = center;
    if (center == 1.0) {
        vec4 frag = vec4(intensity, intensity, intensity, intensity);
        gl_FragColor = frag;
    }
    else{
        vec4 frag = vec4(intensity, intensity, intensity, 0.70);
        gl_FragColor = frag;
    }

}




