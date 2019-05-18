precision highp float;

uniform sampler2D u_texture;

varying vec2 v_texcoord;

void main(void)
{
	vec4 texColor = texture2D(u_texture, v_texcoord);
    gl_FragColor = vec4(texColor.rgb, texColor.a);
}
