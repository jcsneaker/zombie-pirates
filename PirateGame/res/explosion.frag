precision highp float;

uniform sampler2D u_texture;

varying vec2 v_texcoord;

uniform float u_shootProgress;

void main(void)
{
	vec4 texColor = texture2D(u_texture, v_texcoord);

	//vec4 colorDiff = vec4(1.0, 1.0, 1.0, 1.0) - texColor;
	//float alpha = colorDiff.r + colorDiff.g + colorDiff.b + colorDiff.a;
    gl_FragColor = vec4(0.5, 0.0, 0.0, 0.0) * (u_shootProgress) + vec4(texColor.rgba);
}
