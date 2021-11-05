#version 120

attribute vec2 a_Position;
attribute float a_Alpha;

uniform float u_ObjectScale;
uniform vec2 u_Offset;

//varying vec4 v_Color;
varying vec2 v_UVCoord;

void main()
{
    vec2 pos = a_Position*u_ObjectScale + u_Offset;

    gl_Position = vec4( pos/50.0, 0.0, 1.0 );

    //v_Color = vec4( 0.0, a_Alpha, 0.0, 1.0 );
    v_UVCoord = a_Position / 10;
}
