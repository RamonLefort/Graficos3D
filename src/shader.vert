#version 330

in vec3 a_vertex;
in vec3 a_color;

uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

out vec3 v_color;

in vec2 a_uv;
out vec2 v_uv;

in vec3 a_normal;
out vec3 v_normal;
out vec3 v_vertex;

void main()
{
	// position of the vertex
	gl_Position = u_projection * u_view * u_model * vec4( a_vertex , 1.0 );

	// pass the colour to the fragment shader
	v_color = a_color;

	// pass the uv coordinates to the fragment shader
	v_uv = a_uv;

	// pass the normals to the fragment shader
	mat4 normalMatrix = transpose(inverse(u_model));
	v_normal = (normalMatrix * vec4(a_normal, 1.0)).xyz;
	v_vertex = (u_model * vec4( a_vertex , 1.0)).xyz;
}

