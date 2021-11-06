#version 120

uniform sampler2D u_Texture;

varying vec4 v_Color;
varying vec2 v_UVCoord;

void main()
{
    gl_FragColor = v_Color;
    gl_FragColor = texture2D( u_Texture, v_UVCoord );
}
