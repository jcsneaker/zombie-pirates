precision highp float;

uniform mat4 mvpMatrix;

uniform vec4 textureTile;

attribute vec3 a_position;
attribute vec2 a_texcoord;

varying vec2 v_texcoord;

uniform float u_shootProgress;

void main()
{
	vec2 transformedVertex = vec2(1.0 - u_shootProgress * 0.3, 1.0) * a_position.xy;
    gl_Position = mvpMatrix * vec4(transformedVertex, 0.0, 1.0);
    v_texcoord = a_texcoord;
}
