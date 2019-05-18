precision highp float;

uniform sampler2D u_texture;

uniform vec2 u_fadeRange;

varying vec2 v_texcoord;

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
	
    gl_FragColor = vec4(texColor.rgb, texColor.a * getFadeRange());
}
