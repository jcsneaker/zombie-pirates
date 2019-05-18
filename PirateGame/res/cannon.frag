precision highp float;

uniform sampler2D u_texture;

varying vec2 v_texcoord;

uniform vec2 u_fadeRange;
uniform float u_shootProgress;

float getFadeRange()
{
	float fadeStart = u_fadeRange.x;
	float fadeEnd = u_fadeRange.y;

	float alphaFade = 1.0 - (gl_FragCoord.x - fadeStart) / (fadeEnd - fadeStart);
	return clamp(alphaFade, 0.0, 1.0);
}

void main(void)
{
	vec4 texColor = texture2D(u_texture, v_texcoord);

    gl_FragColor = vec4(0.5, 0.0, 0.0, 0.0) * (u_shootProgress) + vec4(texColor.rgb, texColor.a * getFadeRange());
}
