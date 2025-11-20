#version 330

out vec4 fragColor;
in vec2 v_uv;

uniform sampler2D u_texture;

void main(void){
	fragColor = texture(u_texture, v_uv); // RGBA

	//fragColor = vec4(texture(u_texture, v_uv).xyz, 1); // RGBA
}