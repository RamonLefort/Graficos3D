#version 330
uniform vec3 u_color;
uniform vec3 u_light_dir;

in vec2 v_uv;
in vec3 v_color;
in vec3 v_normal;
in vec3 v_vertex;
out vec4 fragColor;

uniform vec3 u_cam_pos;
uniform vec3 u_ambient;
uniform vec3 u_diffuse;
uniform vec3 u_specular;
uniform float u_shininess;
uniform int multitext;

uniform sampler2D u_texture1;
uniform sampler2D u_texture_normal;
uniform sampler2D u_texture_spec;
uniform sampler2D u_texture_night;

mat3 cotangent_frame(vec3 N, vec3 p, vec2 uv)
{   // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx(p);
    vec3 dp2 = dFdy(p);
    vec2 duv1 = dFdx(uv);
    vec2 duv2 = dFdy(uv);

    // solve the linear system
    vec3 dp2perp = cross(dp2, N);
    vec3 dp1perp = cross(N, dp1);
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

    // construct a scale-invariant frame
    float invmax = inversesqrt(max(dot(T, T), dot(B, B)));
    return mat3(T * invmax, B * invmax, N);
}
// assume N, the interpolated vertex normal and
// V, the view vector (vertex to eye)
vec3 perturbNormal(vec3 N, vec3 V, vec2 texcoord, vec3 normal_pixel)
{
    normal_pixel = normal_pixel * 2.0 - 1.0;
    mat3 TBN = cotangent_frame(N, V, texcoord);
    return normalize(TBN * normal_pixel);
}

void main()
{
    vec3 texture_normal = texture(u_texture_normal, v_uv).xyz;
    vec3 texture_color = texture(u_texture1, v_uv).xyz;
    vec3 N = normalize(v_normal);
    vec3 texture_night = texture(u_texture_night, v_uv).xyz;

    //original normal
    vec3 N_orig = N;

    if(multitext == 1){
        // call the function to modify the normal
        N = perturbNormal(N, v_vertex, v_uv, texture_normal);

        // mix the original normal with the new normal
        N = mix(N_orig, N, 2.0f);
    }

    vec3 L = normalize(u_light_dir);
    float NdotL = max(dot(N,L), 0.0);

    vec3 E = normalize(u_cam_pos - v_vertex);
    vec3 H = normalize(L + E);
    float NdotH = max( dot(N,H) , 0.0 );


    vec3 spec_color = texture_color * pow (NdotH , u_shininess) * u_specular;
    vec3 diffuse_color = texture_color * NdotL * u_diffuse;
    vec3 ambient_color = texture_color * u_ambient;

    vec3 texture_spec = texture(u_texture_spec, v_uv).xyz;
    vec3 final_color = ambient_color + diffuse_color + spec_color * texture_spec;
    
    if(multitext == 1){
        if (NdotL < 0.001){
            final_color = texture_night;
            // try to blend the textures
        }
    }

    fragColor = vec4(final_color.xyz, 1.0);
}
