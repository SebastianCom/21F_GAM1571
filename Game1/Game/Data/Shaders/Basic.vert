#version 120

attribute vec2 a_Position;
attribute vec4 a_iResolution;
attribute vec4 a_Color;

uniform vec2 u_Offset;
uniform float u_Time;

varying vec4 v_Color;

void main()
{
	vec2 pos = a_Position + u_Offset;
	
	//pos.y += sin( u_Time + a_Position.x) / 5;

	gl_Position = vec4( pos/10, 0.0, 1.0);

	v_Color = a_Color;
}
