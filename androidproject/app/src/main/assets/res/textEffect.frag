precision highp float;

uniform sampler2D u_texture;

varying vec2 v_texcoord;
uniform vec4 u_color;

void main(void)
{
    float textMask = texture2D(u_texture, v_texcoord).r;
    gl_FragColor = vec4(textMask * u_color.rgb, 1.0);
}
