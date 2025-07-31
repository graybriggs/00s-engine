#version 330 core

in vec2 uv_coords;
in vec3 frag_pos;
in vec3 frag_normal;

out vec4 color;

uniform sampler2D tex_sampler0;
//uniform sampler2D tex_sampler1;
//uniform sampler2D tex_sampler[5];

//uniform int tex_id;

uniform vec3 light_pos;
uniform vec3 light_color;

void main(){

    float luminance = 0.8;
    vec3 ambient_color = vec3(0.5);
    vec3 light_color = vec3(0.2, 0.3, 0.9);
    vec3 light_pos = vec3(20.0, 3.0, -20.0);

    vec3 distance = light_pos - frag_pos;

    vec3 norm = normalize(frag_normal);
    vec3 light_dir = normalize(light_pos - frag_pos);

    float diff = max(dot(norm, -light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 tex_color;
    //if (tex_id == 1)
	    tex_color = texture(tex_sampler0, uv_coords).rgb;
    //else
        //tex_color = texture(tex_sampler1, uv_coords).rgb;

    vec3 res_t1 = luminance * (ambient_color + diffuse) * tex_color;// / distance * distance;

	color = vec4(res_t1, 1.0);
	//color = texture(tex_sampler0, uv_coords);// * vec4(res,1.0);
	//color = texture(tex_sampler1, uv_coords) * vec4(res, 1.0);
}