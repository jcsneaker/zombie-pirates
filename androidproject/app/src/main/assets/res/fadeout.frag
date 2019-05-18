precision highp float;

uniform float u_fadeFactor;

varying vec2 v_texcoord;

void main(void)
{
	gl_FragColor = vec4(0.0, 0.0, 0.0, u_fadeFactor);
}
