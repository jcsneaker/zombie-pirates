precision highp float;

uniform mat4 mvpMatrix;

attribute vec3 a_position;
attribute vec2 a_texcoord;

varying vec2 v_texcoord;

void main()
{
	vec2 transformedVertex = a_position.xy;
    gl_Position = mvpMatrix * vec4(transformedVertex, 0.0, 1.0);
    v_texcoord = a_texcoord;
}
