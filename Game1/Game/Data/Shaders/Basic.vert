#version 120

attribute vec2 a_Position;
uniform vec2 u_Offset;

void main()
{
	gl_Position = vec4( a_Position + u_Offset, 0.0, 1.0);
}
