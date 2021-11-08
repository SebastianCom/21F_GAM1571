#version 120

attribute vec2 a_Position;
attribute vec4 a_iResolution;
attribute vec4 a_Color;

uniform vec2 u_Offset;
uniform float u_Time;
uniform float u_ColorShift;

uniform float u_Scale;

varying vec4 v_Color;
varying float v_ColorShift;

void main()
{
	vec2 pos = (a_Position * u_Scale + u_Offset);
	//pos *= u_Scale;
	//pos.y += sin( u_Time + a_Position.x) / 5;
	float x = 0;
	float y = 100;
	


	gl_Position = vec4( pos / 15 , 0.0, 1.0);
	v_Color = a_Color;
	v_ColorShift = u_ColorShift;
}
