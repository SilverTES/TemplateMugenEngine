#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D tex; // 0
uniform vec2 center; // Mouse position
uniform float time; // effect elapsed time
uniform vec3 shockParams; // 10.0, 0.8, 0.1

uniform vec2 surface; // texture resolution

void main()
{
    vec2 uv = gl_TexCoord[0].xy;

    //vec2 uv = gl_FragCoord.xy;

    vec2 texCoord = uv;

    //float square = min(surface.x,surface.y);
    //vec2 position = vec2(center.x/square, center.y/square);

    vec2 position = center/surface;
    float dist = distance(uv, position);

    //float dist = distance(vec2(uv.x,uv.y), vec2(position.x,position.y));

    if ((dist <= (time + shockParams.z)) && (dist >= (time - shockParams.z)) )
    {
        float diff = (dist - time);
        float powDiff = 1.0 - pow(abs(diff*shockParams.x), shockParams.y);
        float diffTime = diff  * powDiff;
        vec2 diffUV = normalize(uv - position);
        texCoord = uv + (diffUV * diffTime);
    }

    gl_FragColor = texture2D(tex, texCoord);
}



//#version 120
//#ifdef GL_ES
//precision mediump float;
//#endif
//uniform sampler2D al_tex;
//
//uniform float bitmap_width;
//uniform float bitmap_height;
//uniform float x_scale;
//uniform float y_scale;
//
//varying vec4 varying_color;
//varying vec2 varying_texcoord;
//
//void main()
//{
//	vec2 sz = vec2(bitmap_width, bitmap_height);
//	vec3 step = vec3(1.0 / x_scale, 1.0 / y_scale, 0);
//	vec2 tex_pixel = sz * varying_texcoord - step.xy / 2;
//
//	vec2 corner = floor(tex_pixel) + 1;
//	vec2 frac = min((corner - tex_pixel) * vec2(x_scale, y_scale), vec2(1.0, 1.0));
//
//	vec4 c1 = texture2D(al_tex, (floor(tex_pixel + step.zz) + 0.5) / sz);
//	vec4 c2 = texture2D(al_tex, (floor(tex_pixel + step.xz) + 0.5) / sz);
//	vec4 c3 = texture2D(al_tex, (floor(tex_pixel + step.zy) + 0.5) / sz);
//	vec4 c4 = texture2D(al_tex, (floor(tex_pixel + step.xy) + 0.5) / sz);
//
//	c1 *=        frac.x  *        frac.y;
//	c2 *= (1.0 - frac.x) *        frac.y;
//	c3 *=        frac.x  * (1.0 - frac.y);
//	c4 *= (1.0 - frac.x) * (1.0 - frac.y);
//
//	gl_FragColor = varying_color * (c1 + c2 + c3 + c4);
//
//}

//#ifdef GL_ES
//precision mediump float;
//#endif
//
//uniform sampler2D al_tex;
//uniform vec3 tint;
//
//varying vec4 varying_color;
//varying vec2 varying_texcoord;
//
//void main()
//{
//
//    vec4 tmp = varying_color * texture2D(al_tex, varying_texcoord);
//    tmp.r *= tint.r;
//    tmp.g *= tint.g;
//    tmp.b *= tint.b;
//    gl_FragColor = tmp;
//
//
//}




//uniform sampler2D al_tex;
//
//void main()
//{
//    float dx = 15.*(1./512.);
//    float dy = 10.*(1./512.);
//
//    vec2 coord = vec2(dx*floor(gl_TexCoord[0].x/dx), dy*floor(gl_TexCoord[0].y/dy));
//
//    gl_FragColor = texture2D(tex, coord);


//}

//#ifdef GL_ES
//precision mediump float;
//#endif
//
//uniform vec2 lightpos;
//uniform vec3 lightColor;
//uniform float screenHeight;
//uniform vec3 lightAttenuation;
//uniform float radius;
//
//uniform sampler2D al_tex;
//
//void main()
//{
//    vec2 pixel        = gl_FragCoord.xy;
//    pixel.y           = screenHeight-pixel.y;
//    vec2 aux          = lightpos-pixel;
//    float distance    = length(aux);
//
//    float attenuation = 1.0/(lightAttenuation.x + lightAttenuation.y * distance + lightAttenuation.z * distance * distance);
//
//    vec4 color        = vec4(attenuation,attenuation,attenuation,1.0)*vec4(lightColor,1.0);
//
//    gl_FragColor      = color;//*texture2D(texture,gl_TexCoord[0].st);
//}

//uniform sampler2D al_tex;
//uniform float radius;
//
//varying vec4 varying_color;
//varying vec2 varying_texcoord;
//
//void main ()
//{
//    vec2 pos = mod(gl_FragCoord.xy, vec2(40.0)) - vec2(20.0);
//    //vec2 pos = vec2(gl_FragCoord.x-320,gl_FragCoord.y-180);
//    //vec2 pos = vec2(320.0,180.0);
//
//    float dist_squared = dot(pos, pos);
//
//    //vec4 tmp = varying_color * texture2D(al_tex, varying_texcoord);
//    vec4 tmp = texture2D(al_tex, varying_texcoord);
//    //vec3 tmp = vec3(0.0, 0.0, 1.0);
//
////    gl_FragColor = (dist_squared < radius)
////        ? vec4(.0+tmp.r, .0+tmp.g, .0+tmp.b, 1.0)
////        : vec4(0.0, 0.0, 0.0, 0.0);
//
//    if (dist_squared < radius && (tmp.r>0 || tmp.g>0 || tmp.b>0) )
//        gl_FragColor = vec4(.0+tmp.r, .0+tmp.g, .0+tmp.b, 1.0);
//    else
//        gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
//
//    //gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
//}



//uniform sampler2D al_tex;
//uniform float pixel_threshold;
//
//void main()
//{
//    float factor = 1.0 / (pixel_threshold + 0.001);
//    vec2 pos = floor(gl_TexCoord[0].xy * factor + 0.5) / factor;
//    gl_FragColor = texture2D(al_tex, pos) * gl_Color;
//}
//

