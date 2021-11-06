#version 120

varying vec4 v_Color;
varying float v_ColorShift;


void main()
{
	
	gl_FragColor = v_Color * v_ColorShift;
}