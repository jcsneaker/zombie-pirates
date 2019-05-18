precision highp float;

uniform sampler2D u_texture;

uniform vec2 u_fadeRange;

varying vec2 v_texcoord;

void main(void)
{
	vec4 texColor = texture2D(u_texture, v_texcoord);
	
	float fadeStart = u_fadeRange.x;
	float fadeEnd = u_fadeRange.y;

	float alphaFade = 1.0 - (gl_FragCoord.x - fadeStart) / (fadeEnd - fadeStart);
	float clamped = clamp(alphaFade, 0.0, 1.0);
	
	gl_FragColor = vec4(texColor.rgb, texColor.a * clamped);

	//if(gl_FragCoord.x > u_clipX.x && gl_FragCoord.x < u_clipX.y)
	//{
	//	gl_FragColor = vec4(texColor.rgb, texColor.a * );
	//}
	//else
	//{
	//	discard;
	//}
}
